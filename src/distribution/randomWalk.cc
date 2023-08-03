//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "randomWalk.h"

#include <omnetpp.h>

namespace d6g {

std::map<std::string, cValue> randomWalk::lastDelays;  // key for different modules which call the randomWalk

cValue randomWalk::ned_randomWalk(cComponent *context, cNEDValue argv[], int argc) {
    auto unit = argv[1].getUnit();

    std::string key = context->getFullPath();
    if (argc == 3) {
        key += argv[2].stringValue();
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
