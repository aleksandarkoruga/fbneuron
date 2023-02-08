// PluginFBNeuron.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "FBNeuron.hpp"

static InterfaceTable* ft;

namespace FBNeuron {

FBNeuron::FBNeuron() {
    mCalcFunc = make_calc_function<FBNeuron, &FBNeuron::next>();
    next(1);
}

void FBNeuron::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace FBNeuron

PluginLoad(FBNeuronUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<FBNeuron::FBNeuron>(ft, "FBNeuron", false);
}
