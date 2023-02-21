#pragma once

#include "Neurons.hpp"


#define DEFAULT_NET_SIZE 4

#define DEFAULT_RANGE 4.0f
#define DEFAULT_RANGE_INV 0.25f
#define M_PI           3.14159265358979323846  /* pi */
#define PHASOR_MAX 0x07FFFFFFFFFFF  
#define PHASOR_WRAP PHASOR_MAX-0x01
#define PHASOR_DIV  1.0/(double)PHASOR_MAX

namespace model
{

	Neuron::Neuron():m_nInput(DEFAULT_NET_SIZE), m_value(0.0), m_phase(0ULL), m_count(100000000000ULL), m_bias(std::vector<float>(DEFAULT_NET_SIZE, 1.0f)), m_offset(std::vector<float>(DEFAULT_NET_SIZE, 0.0f))
	{
		ChangeParams();
		ResetCount();
	}
	
	Neuron::Neuron(int size): m_nInput(size), m_value(0.0), m_phase(0ULL), m_count(100000000000ULL), m_bias(std::vector<float>(size, 1.0f)), m_offset(std::vector<float>(size, 0.0f))
	{
		ChangeParams();
		ResetCount();
	}

	void Neuron::ChangeParams()
	{
		++m_count;

		float devAmt = static_cast<float>(1.0 - 1.0 /(1.0+1e-3*static_cast<double>(m_count)));

		for (auto i = 0; i < m_nInput; ++i)
		{

			m_bias[i] += static_cast<float>	(	devAmt*		util::GetRandom());
			m_offset[i] += static_cast<float>(	devAmt *	util::GetRandom());

			m_bias[i] = std::tanh(m_bias[i] * DEFAULT_RANGE_INV) * DEFAULT_RANGE;
			m_offset[i] = std::tanh(m_offset[i] * DEFAULT_RANGE_INV) * DEFAULT_RANGE;

		}

	}

	const float& Neuron::Update(const Layer& prevLayer, const float& variation, const float& freq, const float& freqSpread, const float& modFM, const float& crossFade, const double& sampDur)
	{
		float prevValue = m_value;
		m_value = 0.0f;

		for (auto i=0;i<m_nInput;++i)
		{
			m_value += m_bias[i] * prevLayer[i].GetValue() + m_offset[i];
		}
		auto phase = static_cast<float>(m_phase * PHASOR_DIV);
		m_value =  std::sin(static_cast<float>(M_PI)*2.0f*(   (phase*m_value*crossFade) + (1.0f - crossFade)* (phase + m_value)     )  );

		if (std::abs(m_value - prevValue) < variation*sampDur)
		{
			ChangeParams();
		}
		else { ResetCount(); }
		

		m_phase += static_cast<unsigned long long>(static_cast<double> (PHASOR_MAX)*static_cast<double>( freq*sampDur*freqSpread)*  ((1.0 +static_cast<double>( modFM) *static_cast<double> (m_value))));
		m_phase &= PHASOR_WRAP;



		return m_value;
	}

	int nearestPowerOfTwo(int n)
	{
		int v = n;

		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++; // next power of 2

		int x = v >> 1; // previous power of 2

		return (v - n) > (n - x) ? x : v;
	}

	NeuralNet::NeuralNet() : m_outVal(0.0), m_nLayers(DEFAULT_NET_SIZE),m_net(Net(DEFAULT_NET_SIZE, Neuron::Layer(DEFAULT_NET_SIZE,Neuron()) ))
	{
		
	}
	
	NeuralNet::NeuralNet(int size) : m_outVal(0.0), m_nLayers(nearestPowerOfTwo(size)),m_net(Net(nearestPowerOfTwo(size), Neuron::Layer(nearestPowerOfTwo(size),Neuron()) ))
	{
		
	}

	void NeuralNet::Update(const float& variation, const float& freq, const float& freqSpread, const float& modFM, const float& crossFade, const double& sampDur)
	{
		float outVal = 0.0;
		model::Neuron::Layer* prevLayer=nullptr;

		for (auto i = 0; i < m_nLayers; ++i)
		{
			prevLayer = &(m_net[(i + m_nLayers - 1) & (m_nLayers - 1)]);

			for (int j=0; j < m_net[i].size(); ++j)
			{
				outVal+=m_net[i][j].Update(*prevLayer, variation,freq, (1.0f+freqSpread*static_cast<float>(j)/ static_cast<float>(m_net[i].size())), modFM, crossFade, sampDur);
			}
		}
		m_outVal = outVal / (m_nLayers*m_net[0].size());
	}

}