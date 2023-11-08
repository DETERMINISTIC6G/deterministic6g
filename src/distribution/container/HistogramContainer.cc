/*
 * HistogramContainer.cpp
 *
 *  Created on: Oct 31, 2023
 *      Author: dan
 */

#include "HistogramContainer.h"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"
#include "fstream"


namespace d6g {

using namespace inet::xmlutils;

Define_Module(HistogramContainer);

void HistogramContainer::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        histograms.clear();

        auto histogramsMap = check_and_cast<cValueMap *>(par("histograms").objectValue());
        auto histogramsFields = histogramsMap->getFields();

        for (auto &histogramsField: histogramsFields) {
            auto streamName = histogramsField.first;
            auto xmlFile = histogramsField.second.stringValue();
            histograms[streamName] = getHistogram(xmlFile);
            EV << histograms[streamName] << std::endl;

        }
    }
}

Histogram* HistogramContainer::getHistogram(const char* xmlName) {
    std::ifstream infile(xmlName);
    if (!infile) {
        throw cRuntimeError("File '%s' not found", xmlName);
    }

    cXMLElement* xmlData = getEnvir()->getXMLDocument(xmlName);

    if (!xmlData || strcmp(xmlData->getTagName(), "histogram") != 0) {
            throw cRuntimeError("Invalid XML data for histogram");
    }

     // Create a new Histogram instance
     Histogram* histogram = new Histogram();

     // Parse the histogram configuration
     histogram->parseHistogramConfig(xmlData);

     return histogram;
}

} /* namespace d6g */
