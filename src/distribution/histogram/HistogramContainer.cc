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
            histograms[streamName] = loadHistogramFromFile(xmlFile);
            EV << histograms[streamName] << std::endl;

        }
    }
}

Histogram* HistogramContainer::loadHistogramFromFile(const char* fileName) {
    std::ifstream infile(fileName);
    if (!infile) {
        throw cRuntimeError("File '%s' not found", fileName);
    }

    cXMLElement* xmlData = getEnvir()->getXMLDocument(fileName);

    if (!xmlData || strcmp(xmlData->getTagName(), "histogram") != 0) {
            throw cRuntimeError("Invalid XML data for histogram");
    }

     // Create a new Histogram instance
     auto* histogram = new Histogram();

     // Parse the histogram configuration
     histogram->parseHistogramConfig(xmlData);

     infile.close();

     return histogram;
}

cValue HistogramContainer::getRand(std::string key) const {
    auto histogram = getHistogram(key);
    return histogram->getRand();
}

Histogram *HistogramContainer::getHistogram(std::string key) const {
    auto it = histograms.find(key);
    if (it == histograms.end()) {
        throw cRuntimeError("Histogram '%s' not found", key.c_str());
    }
    return it->second;
}

HistogramContainer::~HistogramContainer() {
    for (auto &histogram: histograms) {
        delete histogram.second;
    }
}

} /* namespace d6g */
