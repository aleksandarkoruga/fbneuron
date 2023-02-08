// PluginFBNeuron.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace FBNeuron {

class FBNeuron : public SCUnit {
public:
    FBNeuron();

    // Destructor
    // ~FBNeuron();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace FBNeuron
