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

#ifndef __PKDELAY_HISTOGRAM_H_
#define __PKDELAY_HISTOGRAM_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"

using namespace omnetpp;

namespace d6g {
using namespace inet;

/**
 * TODO - Generated class
 */
class INET_API Histogram : public cSimpleModule
{
    class INET_API BinEntry {
       public:
           BinEntry(cXMLElement *binEntity);
           double left_boundary = -1;
           double right_boundary = -1;
           int count = 0;
           ~BinEntry() = default;
       };

private:
    // Vector to store the bins
    std::list<BinEntry> bins;

protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    void parseHistogramConfig(cXMLElement *histogramEntity);


public:

    // Get Total count of elements in all bins
    void GetNumberElements();
    // Get Number of bins
    void GetNumberBins();
    // Get a random bin with the probability corresponding to the count
    void RandomBin();

   // SUBCLASS BIN
    // left boundary
    // right boundary
    // count of elements in bin

};

} //namespace

#endif
