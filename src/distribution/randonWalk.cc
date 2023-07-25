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

#define MAX_VALUE 9.22e+6
#define MIN_VALUE -9.22e+6

namespace pkdelay {

double randonWalk::cur_delay = 0.0;
int randonWalk::count = 0;

std::map<std::string, double> randonWalk::conversionFactors = {
    {"s", 1},
    {"ms", 1e-3},
    {"us", 1e-6}
};

randonWalk::randonWalk() {
    // TODO Auto-generated constructor stub

}

randonWalk::~randonWalk() {
    // TODO Auto-generated destructor stub
}

cNEDValue randonWalk::ned_randonWalk(cComponent *context, cNEDValue argv[], int argc){
    // Retrieve the time units from the input parameters
    const char* unit0 = argv[0].getUnit();
    const char* unit1 = argv[1].getUnit();

//    EV << "unit0: " << unit0 << " -- unit1: " << unit1 << "\n";
    // Convert the input parameters to double, according to their respective time units
    double arg0 = argv[0].doubleValueInUnit(unit0);
    double arg1 = argv[1].doubleValueInUnit(unit1);
    EV << "Initial Value: arg0: " << arg0 << unit0 << " -- arg1: " << arg1 << unit1 << "\n";

    if(strcmp(unit0, unit1) != 0){
        arg1 = arg1 * conversionFactors[unit1] / conversionFactors[unit0]; // Converts arg1 from its original unit (unit1) to the target unit (unit0)
//        unit1 = unit0; // align unit1 to unit0 after conversion
        EV << "arg0: " << arg0 << unit0 << " -- arg1: " << arg1 << unit0 << "\n";
    }

    // Calculate the delay time. If it's the first calculation (count == 0), set the delay to arg0.
    // In subsequent calculations, increment the current delay by the sum of the previous delay and arg1.
    // Also, ensure the delay never goes below 0.
    cur_delay = (count == 0) ? arg0 : cur_delay + arg1;
    cur_delay = std::max(0.0, cur_delay);
//    cur_delay = std::min(MAX_VALUE, std::max(MIN_VALUE, cur_delay));

    EV << "Calculated cur_delay: " << (count == 0 ? "Initial " : "") << cur_delay << unit0 << "\n";
    if (cur_delay == 0) {
        EV << "Calculated delay is negative. Setting delay to 0.\n";
    }

    count++;

    return cNEDValue(clocktime_t(cur_delay).dbl(), unit0);  // change "us" to non hard-coded
}

Define_NED_Function(randonWalk::ned_randonWalk, "any randonwalk(any init, any randValue)");

} /* namespace pkdelay */
