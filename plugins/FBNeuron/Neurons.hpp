#pragma once
#include <vector>
#include <cmath>
#include <random>

namespace model {

	namespace util
	{
		static std::random_device s_randomDevice;  // Will be used to obtain a seed for the random number engine
		static std::mt19937 s_randomGenerator(s_randomDevice()); // Standard mersenne_twister_engine seeded with rd()
		static std::uniform_real_distribution<> s_uniformDistribution(-1.0, 1.0);
		static double GetRandom() { return s_uniformDistribution(s_randomGenerator); }
	}

	class Neuron {
	public:

		typedef std::vector<Neuron> Layer;
		Neuron();
		Neuron(int size);
		inline const float& GetValue() const { return m_value; };
		void ChangeParams();
		inline void ResetCount() { m_count = 0ULL; }
		const float& Update(const Layer& prevLayer, const float& variation, const float& freq, const float& freqSpread, const float& mod, const float& mod2, const double& sampDur);
		int EnumerateNeurons() { return m_nInput; }

	protected:

		int m_nInput;

		float m_value;
		unsigned long long m_phase;
		int64_t m_count;

		std::vector<float> m_bias;

		std::vector<float> m_offset;

		

	};
	
	class NeuralNet {
	public:
		typedef std::vector<Neuron::Layer> Net;

		NeuralNet();
		NeuralNet(int size);
		void Update(const float& variation, const float& freq, const float& freqSpread, const float& mod, const float& mod2, const double& sampDur);
		inline const Neuron::Layer& GetLayer(unsigned int layer) { return m_net[layer&(m_nLayers-1U)]; }
		inline const float& GetSummedNodes() { return m_outVal; };
	protected:
		
		float m_outVal;

		int m_nLayers;

		Net m_net;

	};
}
