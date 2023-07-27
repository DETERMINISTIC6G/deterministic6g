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
    for (auto &binEntity : binEntities) {
        // TODO: Store bins somewhere. You need to declare a container to hold the bins in the Histogram class.
        auto *histogramEntry = new BinEntry(binEntity);
        EV << "Histogram: Bin at " << histogramEntry->count << endl;
        EV << "Histogram: low = " << histogramEntry->left_boundary << endl;

            // add to list
    }
}



void d6g::Histogram::GetNumberElements() {
    // TODO: Iterate over your bins and sum up the counts.
}

void d6g::Histogram::GetNumberBins() {
    // TODO: Return the size of your bin container.
}

void d6g::Histogram::RandomBin() {
    // TODO: Implement random bin selection based on count.
}

d6g::Histogram::BinEntry::BinEntry(cXMLElement *binEntity) {
    const char* lowAttr = binEntity->getAttribute("low");

    if (strcmp(lowAttr, "-inf") == 0) {
        this->left_boundary = -std::numeric_limits<double>::infinity();
    } else {
        this->left_boundary = atof(lowAttr);
    }

    this->count = atoi(binEntity->getNodeValue());
}
