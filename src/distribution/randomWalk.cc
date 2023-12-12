// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "randomWalk.h"

#include <omnetpp.h>

namespace d6g {

std::map<std::string, cValue> randomWalk::lastDelays;  // key for different modules which call the randomWalk

cValue randomWalk::ned_randomWalk(cComponent *context, cNEDValue argv[], int argc) {
    auto unit = argv[1].getUnit();

    std::string key = context->getFullPath();
    if (argc == 3) {
        key = argv[2].stringValue();
    }

    // Check if the key is already in the map
    if (lastDelays.find(key) == lastDelays.end()) {
        // If not, add it
        double initialDelay = argv[0].doubleValueInUnit(unit);
        lastDelays[key] = cValue(initialDelay, unit);
    }

    auto lastDelay = lastDelays[key].doubleValueInUnit(unit);

    // Calculate the new delays based on the last delay and a random value from a given distribution
    // Also, ensure the delay never goes below 0.
    double randomWalkNextValue = argv[1].doubleValueInUnit(unit);
    double nextDelayDbl = lastDelay + randomWalkNextValue;
    cValue nextDelay = cValue(std::max(nextDelayDbl, 0.0), unit);
    lastDelays[key] = nextDelay;

    return nextDelay;
}
// randomWalk
Define_NED_Function(randomWalk::ned_randomWalk, "quantity randomWalk(quantity init, quantity randValue, string key?)");

} /* namespace d6g */
