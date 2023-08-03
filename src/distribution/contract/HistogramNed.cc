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

#include "HistogramNed.h"

#include <omnetpp.h>
#include "IRandomNumberProvider.h"

namespace d6g {
using namespace inet;

cNEDValue HistogramNed::randomNumberProviderNED(omnetpp::cComponent *context, omnetpp::cNEDValue *argv, int argc) {
    if (argc != 1) {
        // handle error: wrong number of arguments
        throw cRuntimeError("Wrong number of arguments: %d", argc);
    }

    const char* pathToRNG = argv[0].stringValue();
    auto rngModule = context->findModuleByPath(pathToRNG);
    if (rngModule == nullptr) {
        // handle error: module not found
        throw cRuntimeError("Module not found: %s", pathToRNG);
    }
    // Cast to IRandomNumberProvider
    auto rng = check_and_cast<IRandomNumberProvider *>(rngModule);

    return rng->getRand();
}

Define_NED_Function(HistogramNed::randomNumberProviderNED, "quantity rngProvider(string histogramModule)");

} /* namespace d6g */
