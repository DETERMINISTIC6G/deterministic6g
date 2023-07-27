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

void Histogram::initialize(int stage)
{
    // TODO - Generated method body
    // Parse the histogram configuration
    if (stage == INITSTAGE_LOCAL) {

        cXMLElement *histogramEntity = par("histogramConfig").xmlValue();
        parseHistogramConfig(histogramEntity);
    }
}

void Histogram::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

} //namespace

void d6g::Histogram::parseHistogramConfig(cXMLElement *histogramEntity){
    if (strcmp(histogramEntity->getTagName(), "histogram") != 0) {
        throw cRuntimeError("Cannot read histogram configuration, unaccepted '%s' entity at %s",
                            histogramEntity->getTagName(),
                            histogramEntity->getSourceLocation());
    }

    cXMLElementList binEntities = histogramEntity->getChildrenByTagName("bin");
    BinEntry *previousBinEntry = nullptr;
//    EV << "random Bin: " << randomBin() << endl;
    for (auto &binEntity : binEntities) {
        // TODO: Store bins somewhere. You need to declare a container to hold the bins in the Histogram class.
        auto *currentBinEntry = new BinEntry(binEntity);
//        EV << "Histogram: Bin count " << currentBinEntry->count << endl;
//        EV << "Histogram: low = " << currentBinEntry->leftBoundary << endl;
        totalCount = totalCount + currentBinEntry->count;

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
    for (const BinEntry* bin : bins) {
        EV << "Left boundary: " << bin->leftBoundary
           << "  --  Right boundary: " << bin->rightBoundary
           << "  --  Count: " << bin->count << endl;
    }

    EV << "Number of bins: " << getNumberBins() << endl;

    EV << "random Bin: " << randomBin() << endl;
    EV << "random Bin: " << randomBin() << endl;
    EV << "random Bin: " << randomBin() << endl;
    EV << "random Bin: " << randomBin() << endl;

}



int d6g::Histogram::getTotalCount() {
    // TODO: Iterate over your bins and sum up the counts.
    return totalCount;
}

int d6g::Histogram::getNumberBins() {
    // TODO: Return the size of your bin container.
    return bins.size();
}

double d6g::Histogram::randomBin() {
    // TODO: Implement random bin selection based on count.
    if(totalCount == 0) {
        throw cRuntimeError("No bins to select from");
    }

    // Generate a random number between 0 and totalCount
    int randomValue = getRNG(0)->intRand(totalCount);

    // Iterate through the bins
    int runningTotal = 0;
    for(auto binEntry : bins) {
        runningTotal += binEntry->count;
        if(runningTotal > randomValue) {
            // This is the selected bin
            return binEntry->leftBoundary;  // Or rightBoundary, or some other value you want to return
        }
    }

    throw cRuntimeError("totalCount is 0. This should never happen, check your totalCount calculation");
}

d6g::Histogram::BinEntry::BinEntry(cXMLElement *binEntity) {
    const char* lowAttr = binEntity->getAttribute("low");

    if (strcmp(lowAttr, "-inf") == 0) {
        this->leftBoundary = -std::numeric_limits<double>::infinity();
    } else {
        this->leftBoundary = atof(lowAttr);
    }

    this->count = atoi(binEntity->getNodeValue());
}
