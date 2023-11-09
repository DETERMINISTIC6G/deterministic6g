//
// Created by haugls on 7/28/23.
//

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
    virtual cValue getRand() const = 0;
    virtual cValue getRand(std::string key) const = 0;
    static cNEDValue randomNumberProviderNED(cComponent *context, cNEDValue argv[], int argc);
};
}

#endif
