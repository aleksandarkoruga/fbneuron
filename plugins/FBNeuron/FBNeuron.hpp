// PluginFBNeuron.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include <memory>
namespace model { class NeuralNet; }

namespace FBNeuron {

class FBNeuron : public SCUnit {
public:
    FBNeuron();

    // Destructor
    // ~FBNeuron();

private:
    // Calc function
    void next(int nSamples);
    std::unique_ptr<model::NeuralNet> m_net;
    // Member variables
};

} // namespace FBNeuron
