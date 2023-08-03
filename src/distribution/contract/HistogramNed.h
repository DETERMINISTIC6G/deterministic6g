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

#ifndef DISTRIBUTION_HISTOGRAM_HISTOGRAMNED_H_
#define DISTRIBUTION_HISTOGRAM_HISTOGRAMNED_H_

#include <omnetpp.h>
#include "inet/linklayer/base/MacRelayUnitBase.cc"

namespace d6g {
using namespace inet;

class HistogramNed : public cSimpleModule {
public:
    static cNEDValue randomNumberProviderNED(cComponent *context, cNEDValue argv[], int argc);
};

} /* namespace d6g */

#endif /* DISTRIBUTION_HISTOGRAM_HISTOGRAMNED_H_ */
