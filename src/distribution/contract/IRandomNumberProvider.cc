// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "IRandomNumberProvider.h"

namespace d6g {
using namespace inet;

cNEDValue IRandomNumberProvider::randomNumberProviderNED(omnetpp::cComponent *context, omnetpp::cNEDValue *argv, int argc) {
    if (argc < 1 || argc > 2) {
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

    if (argc == 2) {
        // Get the key
        const char* key = argv[1].stringValue();
        return rng->getRand(key);
    } else {
        return rng->getRand();
    }
}

Define_NED_Function(IRandomNumberProvider::randomNumberProviderNED, "quantity rngProvider(string rngProviderModule, string key?)");

} /* namespace d6g */
