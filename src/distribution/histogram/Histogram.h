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
           double leftBoundary = -1;
           double rightBoundary = -1;
           int count = 0;
           ~BinEntry() = default;
       };

private:
    // Vector to store the bins
    std::list<BinEntry*> bins;
    int totalCount;
    int countBins;

protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    void parseHistogramConfig(cXMLElement *histogramEntity);


public:

    // Get Total count of elements in all bins
    int getTotalCount();
    // Get Number of bins
    int getNumberBins();
    // Get a random bin with the probability corresponding to the count
    double randomBin();

   // SUBCLASS BIN
    // left boundary
    // right boundary
    // count of elements in bin

};

} //namespace

#endif
