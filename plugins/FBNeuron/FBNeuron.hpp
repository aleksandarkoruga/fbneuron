// PluginFBNeuron.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include "Neurons.hpp"

namespace FBNeuron {

class FBNeuron : public SCUnit {
public:
    FBNeuron();

    // Destructor
    // ~FBNeuron();

private:
    // Calc function
    void next(int nSamples);
    model::NeuralNet m_net;
    // Member variables
};

} // namespace FBNeuron
