// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DETERMINISTIC6G_HISTOGRAMCONTAINER_H_
#define DETERMINISTIC6G_HISTOGRAMCONTAINER_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include "../contract/IRandomNumberProvider.h"
#include "../histogram/Histogram.h"

using namespace omnetpp;

namespace d6g {
using namespace inet;

class INET_API HistogramContainer : public cSimpleModule, public IRandomNumberProvider {

private:
    std::map<std::string, Histogram*> histograms;

protected:
    virtual void initialize(int stage) override;
    static Histogram* loadHistogramFromFile(const char* fileName);
public:
    Histogram* getHistogram(std::string key) const;
    cValue getRand() override {
        throw cRuntimeError("HistogramContainer requires a key (name of histogram)");
    }
    cValue getRand(std::string key) override;

    // Destructor
    ~HistogramContainer() override;
};

} /* namespace d6g */

#endif /* DISTRIBUTION_CONTAINER_HISTOGRAMCONTAINER_H_ */
