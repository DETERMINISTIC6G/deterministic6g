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

#include "NedStatic.h"
#include <omnetpp.h>

namespace pkdelay {

NedStatic::NedStatic() {
    // TODO Auto-generated constructor stub

}

NedStatic::~NedStatic() {
    // TODO Auto-generated destructor stub
}

cNEDValue NedStatic::ned_Static(cComponent *context, cNEDValue argv[], int argc)
{
    //NedStatic *instance = dynamic_cast<NedStatic *>(context);
    //if (!instance)
    //    throw cRuntimeError("The ned_Static function can only be called in the context of a PKDelayer object");

    double arg0 = argv[0].doubleValueInUnit("us"); // convert to double

//    clocktime_t delay = clocktime_t(arg0);
//    double staticDelayDbl = delay.dbl(); // convert to double
//    clocktime_t temp =  clocktime_t(staticDelayDbl);
    clocktime_t temp =  clocktime_t(arg0);
    return cNEDValue(temp.dbl(), "us"); // specify unit
}

Define_NED_Function(NedStatic::ned_Static, "any static(any staticDelay)");

} /* namespace pkdelay */
