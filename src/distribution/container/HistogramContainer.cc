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

        }
    }
}

Histogram* HistogramContainer::getHistogram(const char* xmlName) {
    std::ifstream infile(xmlName);
    if (!infile) {
        throw cRuntimeError("File '%s' not found", xmlName);
    }



    cXMLElement* xmlData;
    //may needed to make it more simply
    std::string line;
    while (std::getline(xmlFile, line)) {
           // Process each line of the XML file here
           if (line.find('<') != std::string::npos && line.find('>') != std::string::npos) {

               // Extract the element name and content
               size_t start = line.find('<') + 1;
               size_t end = line.find('>');

               if (start != std::string::npos && end != std::string::npos) {
                   xmlData.key = line.substr(start, end - start);

                   size_t contentStart = end + 1;
                   size_t contentEnd = line.find('<', contentStart);
                   if (contentEnd != std::string::npos) {
                       xmlData.value = line.substr(contentStart, contentEnd - contentStart);
                   }
               }
           }
       }
    //Is xmlData an array, a link list or something else? it should store all xml elements in xml file, rather than only one element








    //cXMLElement* xmlData = par(xmlName).xmlValue();
    if (!xmlData || strcmp(xmlData->getTagName(), "histogram") != 0) {
            throw cRuntimeError("Invalid XML data for histogram");
        }

     // Create a new Histogram instance
     Histogram* histogram = new Histogram();

     // Parse the histogram configuration
     histogram->parseHistogramConfig(xmlData);

     infile.close();

     return histogram;
}

} /* namespace d6g */
