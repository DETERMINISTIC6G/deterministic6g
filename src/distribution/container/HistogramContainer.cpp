/*
 * HistogramContainer.cpp
 *
 *  Created on: Oct 31, 2023
 *      Author: dan
 */

#include "HistogramContainer.h"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"

namespace d6g {

using namespace inet::xmlutils;

Define_Module(HistogramContainer);

void HistogramContainer::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        // Get the histogram configurations from the parameters
        std::map<std::string, cXMLElement*> histogramConfigs = par("histograms").xmlValue();
        for (const auto& [name, config]: histogramConfigs) {
            Histogram* histogram = new Histogram();
            histogram->Histogram::parseHistogramConfig(config);  // You might need to add this method to your Histogram class
            histograms[name] = histogram;
        }
    }
}

Histogram* HistogramContainer::getHistogram(const std::string& name) {
    if (histograms.find(name) != histograms.end()) {
        return it->second;
    } else {
        throw cRuntimeError("Histogram not found: %s", name.c_str());
    }
}

} /* namespace d6g */
