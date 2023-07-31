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

#include "Histogram.h"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"

namespace d6g {

using namespace inet::xmlutils;

Define_Module(Histogram);

void Histogram::initialize(int stage) {
    // Parse the histogram configuration
    if (stage == INITSTAGE_LOCAL) {
        cXMLElement *histogramEntity = par("histogramConfig").xmlValue();
        parseHistogramConfig(histogramEntity);
    }
}

void Histogram::parseHistogramConfig(cXMLElement *histogramEntity) {
    if (strcmp(histogramEntity->getTagName(), "histogram") != 0) {
        throw cRuntimeError("Cannot read histogram configuration, unaccepted '%s' entity at %s",
                            histogramEntity->getTagName(),
                            histogramEntity->getSourceLocation());
    }

    cXMLElementList binEntities = histogramEntity->getChildrenByTagName("bin");
    BinEntry *previousBinEntry = nullptr;

    for (auto &binEntity: binEntities) {
        auto *currentBinEntry = new BinEntry(binEntity);

        totalCount += currentBinEntry->count;

        if (previousBinEntry != nullptr) {
            previousBinEntry->rightBoundary = currentBinEntry->leftBoundary;
        }

        // add to list
        bins.push_back(currentBinEntry);

        previousBinEntry = currentBinEntry;
    }

    if (previousBinEntry != nullptr) {
        previousBinEntry->rightBoundary = std::numeric_limits<double>::infinity();
    }

    // Check the bins
    for (const auto *bin: bins) {
        EV << "Left boundary: " << bin->leftBoundary
           << "  --  Right boundary: " << bin->rightBoundary
           << "  --  Count: " << bin->count << endl;
    }

    EV << "Random Bin 1: " << randomBin()->leftBoundary << endl;
    EV << "Random Bin 2: " << randomBin()->leftBoundary << endl;
    EV << "Random Bin 3: " << randomBin()->leftBoundary << endl;
    EV << "Random Bin 4: " << randomBin()->leftBoundary << endl;
    EV << "Random Bin 5: " << randomBin()->leftBoundary << endl;
    EV << "Random Bin 6: " << randomBin()->leftBoundary << endl;
    EV << "Random Bin 7: " << randomBin()->leftBoundary << endl;
}

int Histogram::getTotalCount() const {
    return totalCount;
}

size_t Histogram::getNumberBins() const {
    return bins.size();
}

Histogram::BinEntry *Histogram::randomBin() const {
    if (totalCount == 0) {
        throw cRuntimeError("No bins to select from");
    }

    // Generate a random number between 0 and totalCount
    auto randomValue = intrand(totalCount);

    std::vector<int> prefixSums;
    prefixSums.resize(bins.size());
    int runningTotal = 0;
    int i = 0;
    for(auto &binEntry : bins) {
        runningTotal += binEntry->count;
        prefixSums[i] = runningTotal;
        i++;
    }

    //Binary Search
    return BinarySearch(randomValue, 0, getNumberBins()-1, prefixSums);
}

Histogram::BinEntry *Histogram::BinarySearch(int target, int low, int high, const std::vector<int>& prefixSums) const {
    if (low > high) {
        if (low < bins.size()) {
            auto it = bins.begin();
            std::advance(it, low);
            return *it;
        }
        throw cRuntimeError("random number greater than actual total count. This should never happen, check your totalCount calculation");
    }

    int mid = low + ((high - low) / 2);

    if (target < prefixSums[mid]){
        return BinarySearch(target, low, mid - 1, prefixSums);
    }
    else if (target > prefixSums[mid]){
        return BinarySearch(target, mid + 1, high, prefixSums);
    }
    else{
        auto it = bins.begin();
        std::advance(it, mid);
        return *it;
    }
}

double Histogram::getRand() const {
    auto bin = randomBin();
    return uniform(bin->leftBoundary, bin->rightBoundary);
}

Histogram::BinEntry::BinEntry(cXMLElement *binEntity) {
    const char *lowAttr = binEntity->getAttribute("low");
    this->leftBoundary = atof(lowAttr);
    this->count = atoi(binEntity->getNodeValue());
}


} //namespace

