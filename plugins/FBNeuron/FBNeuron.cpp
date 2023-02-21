// PluginFBNeuron.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "FBNeuron.hpp"

static InterfaceTable* ft;

namespace FBNeuron {

FBNeuron::FBNeuron() : m_net() {
    mCalcFunc = make_calc_function<FBNeuron, &FBNeuron::next>();
    next(1);
}

void FBNeuron::next(int nSamples) {
    const float* variation = in(0);
    const float* freq = in(1);
    const float* freqSpread = in(2);
    const float* mod = in(3);
    const float* mod2 = in(4);
    float* outbuf = out(0);

    for (int i = 0; i < nSamples; ++i) {
        auto val = sc_abs(variation[i]);
        m_net.Update(val,freq[i],freqSpread[i],mod[i], mod2[i],sampleDur());
        outbuf[i] = m_net.GetSummedNodes();// *gain[i];
     
    }
}

} // namespace FBNeuron

PluginLoad(FBNeuronUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<FBNeuron::FBNeuron>(ft, "FBNeuron", false);
}
