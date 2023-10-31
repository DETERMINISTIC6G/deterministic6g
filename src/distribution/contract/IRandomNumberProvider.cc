//
// Created by haugls on 31.10.23.
//

#include "IRandomNumberProvider.h"

namespace d6g {
using namespace inet;

cNEDValue IRandomNumberProvider::randomNumberProviderNED(omnetpp::cComponent *context, omnetpp::cNEDValue *argv, int argc) {
    if (argc != 1) {
        // handle error: wrong number of arguments
        throw cRuntimeError("Wrong number of arguments: %d", argc);
    }

    const char* pathToRNG = argv[0].stringValue();
    auto rngModule = context->findModuleByPath(pathToRNG);
    if (rngModule == nullptr) {
        // handle error: module not found
        throw cRuntimeError("Module not found: %s", pathToRNG);
    }
    // Cast to IRandomNumberProvider
    auto rng = check_and_cast<IRandomNumberProvider *>(rngModule);

    return rng->getRand();
}

Define_NED_Function(IRandomNumberProvider::randomNumberProviderNED, "quantity rngProvider(string histogramModule)");

} /* namespace d6g */
