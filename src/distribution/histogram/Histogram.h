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

#ifndef DETERMINISTIC6G_HISTOGRAM_H_
#define DETERMINISTIC6G_HISTOGRAM_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include "../contract/IRandomNumberGenerator.h"

using namespace omnetpp;

namespace d6g {
using namespace inet;

/**
 * TODO - Generated class
 */
class INET_API Histogram : public cSimpleModule, public IRandomNumberGenerator {
    class INET_API BinEntry {
    public:
        explicit BinEntry(cXMLElement *binEntity, cModule *context = nullptr);

        cValue leftBoundary = -INFINITY;
        cValue rightBoundary = INFINITY;
        int count = 0;
        int accumulatedCount = 0;  // new member to hold the cumulative count
        ~BinEntry() = default;
    };

private:
    // Vector to store the bins
    std::vector<BinEntry *> bins;
    int totalCount;

protected:
    void initialize(int stage) override;

    void parseHistogramConfig(cXMLElement *histogramEntity);

public:

    // Get Total count of elements in all bins
    int getTotalCount() const;

    // Get Number of bins
    size_t getNumberBins() const;

    // Get a random bin with the probability corresponding to the count
    BinEntry *randomBin() const;

    // Binary Search
    BinEntry *BinarySearch(int target) const;

    cValue getRand() const override;
};

} //namespace

#endif
