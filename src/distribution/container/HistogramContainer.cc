/*
 * HistogramContainer.cpp
 *
 *  Created on: Oct 31, 2023
 *      Author: dan
 */

#include "HistogramContainer.h"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"
#include "iostream"

namespace d6g {

using namespace inet::xmlutils;

Define_Module(HistogramContainer);

void HistogramContainer::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        // Get the histogram configurations from the parameters
        auto histogramsXml = check_and_cast<cValueMap *>(par("histograms").objectValue());
        cXMLElement* histogramXml = nullptr;

        if (histogramsXml != nullptr) {
            // Iterate over all children elements which are histograms
            histogramXml = histogramsXml->getFirstChild();
            while (histogramXml != nullptr) {
                const char* histName = histogramXml->getTagName();
                // Here you would create your Histogram objects based on the XML data
                // For example, if your Histogram constructor takes an XML element:
                histograms[histName] = new Histogram();
                histograms[histName]->parseHistogramConfig(histogramXml);
                // Move to the next histogram element
                histogramXml = histogramXml->getNextSibling();
            }
        }
    }
}

Histogram* HistogramContainer::getHistogram(const std::string& name) {
    if (histograms.find(name) != histograms.end()) {
        return histograms.find(name)->second;
    } else {
        throw cRuntimeError("Histogram not found: %s", name.c_str());
    }
}

} /* namespace d6g */
