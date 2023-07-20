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

#include "randonWalk.h"
#include <omnetpp.h>


namespace pkdelay {

double randonWalk::cur_delay = 0.0;
int randonWalk::count = 0;

randonWalk::randonWalk() {
    // TODO Auto-generated constructor stub

}

randonWalk::~randonWalk() {
    // TODO Auto-generated destructor stub
}

cNEDValue randonWalk::ned_randonWalk(cComponent *context, cNEDValue argv[], int argc){
    double arg0 = argv[0].doubleValueInUnit("us");
    double arg1 = argv[1].doubleValueInUnit("us");

    if (count == 0) {
        cur_delay = arg0;
        EV << "Initial cur_delay: " << cur_delay << "us\n";
    }

    else {
        cur_delay = cur_delay + arg1;
        if(cur_delay < 0){
            EV << "Calculated delay is negative. Setting delay to 0.";
            cur_delay = 0;
        }
        EV << "Calculated cur_delay: " << cur_delay << "us\n";
    }

    clocktime_t tmp = clocktime_t(cur_delay);
    count++;
    return cNEDValue(tmp.dbl(), "us");  // change "us" to non hard-coded
}

Define_NED_Function(randonWalk::ned_randonWalk, "any randonwalk(any init, any randValue)");

} /* namespace pkdelay */
