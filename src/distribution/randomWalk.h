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

#ifndef DISTRIBUTION_RANDOMWALK_H_
#define DISTRIBUTION_RANDOMWALK_H_

#include "inet/queueing/base/PacketDelayerBase.h"

namespace d6g {

using namespace inet;

class randomWalk {
public:
//    static double cur_delay;
//    static int count;

    static std::map<std::string, cValue> lastDelays;  // key for different modules which call the randomWalk

public:
//    double return_delay;
//    double cur_delay;
//    int count = 0;
    static cNEDValue ned_randomWalk(cComponent *context, cNEDValue argv[], int argc);
};

} /* namespace d6g */

#endif /* DISTRIBUTION_RANDOMWALK_H_ */
