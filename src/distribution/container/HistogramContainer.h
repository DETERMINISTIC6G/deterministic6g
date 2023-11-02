/*
 * HistogramContainer.h
 *
 *  Created on: Oct 31, 2023
 *      Author: dan
 */

#ifndef DISTRIBUTION_CONTAINER_HISTOGRAMCONTAINER_H_
#define DISTRIBUTION_CONTAINER_HISTOGRAMCONTAINER_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include "../contract/IRandomNumberProvider.h"
#include "../src/distribution/histogram/Histogram.h"

using namespace omnetpp;

namespace d6g {
using namespace omnetpp;

class INET_API HistogramContainer : public cSimpleModule, public IRandomNumberProvider{

public:
    std::map<std::string, Histogram*> histograms;

public:
    virtual void initialize(int stage) override;
    Histogram* getHistogram(const std::string& name);
};

} /* namespace d6g */

#endif /* DISTRIBUTION_CONTAINER_HISTOGRAMCONTAINER_H_ */
