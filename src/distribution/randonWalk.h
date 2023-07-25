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

#ifndef DISTRIBUTION_RANDONWALK_H_
#define DISTRIBUTION_RANDONWALK_H_

#include "inet/queueing/base/PacketDelayerBase.h"

namespace pkdelay {

using namespace inet;

class randonWalk {
private:
    static double cur_delay;
    static int count;

    static std::map<std::string, double> conversionFactors;

public:
//    double return_delay;
//    double cur_delay;
//    int count = 0;

    randonWalk();
    virtual ~randonWalk();

    static cNEDValue ned_randonWalk(cComponent *context, cNEDValue argv[], int argc);
};

} /* namespace pkdelay */

#endif /* DISTRIBUTION_RANDONWALK_H_ */
