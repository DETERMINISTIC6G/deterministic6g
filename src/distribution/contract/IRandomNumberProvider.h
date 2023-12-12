// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DETERMINISTIC6G_IRANDOMNUMBERPROVIDER_H
#define DETERMINISTIC6G_IRANDOMNUMBERPROVIDER_H

#include <omnetpp.h>
#include "inet/common/INETDefs.h"

namespace d6g {
using namespace inet;

/**
 * Generic Interface for providing random numbers to the simulation.
 */
class IRandomNumberProvider {
public:
    /**
     * Returns a random number.
     * @return random number provided by subclass.
     */
    virtual cValue getRand() {
        throw cRuntimeError("IRandomNumberProvider::getRand() not implemented");
    };

    virtual cValue getRand(const std::string &key) {
        throw cRuntimeError("IRandomNumberProvider::getRand(key) not implemented (called with key %s)", key.c_str());
    };

    static cNEDValue randomNumberProviderNED(cComponent *context, cNEDValue argv[], int argc);
};
}

#endif
