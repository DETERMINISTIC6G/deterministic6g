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
    const char* unit0 = argv[0].getUnit();
    double arg0 = argv[0].doubleValueInUnit(unit0); // convert to double
    EV << "Delay: " << arg0 << unit0 << "\n";
    return cNEDValue(clocktime_t(arg0).dbl(), unit0); // specify unit
}

Define_NED_Function(NedStatic::ned_Static, "any static(any staticDelay)");

} /* namespace pkdelay */
