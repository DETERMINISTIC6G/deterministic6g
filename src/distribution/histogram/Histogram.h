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
#include "../contract/IRandomNumberProvider.h"

using namespace omnetpp;

namespace d6g {
using namespace inet;

/**
 * Histogram is a module that provides a random number based on a histogram configuration.
 * The histogram configuration is provided in the NED file as a parameter.
 * For more information on the histogram configuration, see the NED documentation.
 */
class INET_API Histogram : public cSimpleModule, public IRandomNumberProvider {
    /**
     * BinEntry is a class that represents a bin in the histogram.
     */
public:
    class INET_API BinEntry {
    public:
        explicit BinEntry(cXMLElement *binEntity, cModule *context = nullptr);

        // Left boundary
        cValue leftBoundary = -INFINITY; ///< Left boundary
        cValue rightBoundary = INFINITY; ///< Right boundary
        int count = 0; ///< Count of elements in the bin
        int accumulatedCount = 0; ///< Accumulated count from beginning of the histogram including this bin
        ~BinEntry() = default;
    };

private:
    std::vector<BinEntry *> bins; ///< Vector to store the bins
    int totalCount = 0; ///< Total count of elements in all bins

protected:
    void initialize(int stage) override;
public:
    Histogram();
    ~Histogram();
    void parseHistogramConfig(cXMLElement *histogramEntity);

public:
    /*!
     * Get total count of elements in all bins
     *
     * @return total count of elements in all bins
     */
    int getTotalCount() const;

    /*!
     * Get number of bins
     *
     * @return number of bins
     */
    size_t getNumberBins() const;

    /*!
     * Get a random bin, based on the number of elements in each bin
     *
     * @return random bin
     */
    BinEntry *randomBin() const;

    /*!
     * Get a random number from the histogram.
     * This function uses the randomBin() function to get a random bin, and then returns a random number from that bin's range.
     *
     * @return random number from the histogram
     */
    cValue getRand() const override;
    cValue getRand(std::string key) const override {
        throw cRuntimeError("Histogram does not support random number generation with a key, but %s was provided", key.c_str());
    }

    BinEntry *getBinFromTargetValue(int target) const;

private:
    /*!
     * Self check to make sure that the histogram is correct
     *
     * This was used for debugging purposes, not needed anymore hopefully but keeping it just in case.
     */
    void selfCheck() const;
};

} //namespace

#endif
