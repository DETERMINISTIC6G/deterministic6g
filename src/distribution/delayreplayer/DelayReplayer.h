/*
 * delaypar.h
 *
 *  Created on: Nov 11, 2023
 *      Author: dan
 */

#ifndef DISTRIBUTION_DELAYREPLAYER_DELAYREPLAYER_H_
#define DISTRIBUTION_DELAYREPLAYER_DELAYREPLAYER_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include "../contract/IRandomNumberProvider.h"

using namespace omnetpp;

namespace d6g {
using namespace inet;

class INET_API DelayReplayer : public cSimpleModule, public IRandomNumberProvider{

private:
    std::vector<cValue> delays;
    std::vector<cValue>::iterator delayIterator;

protected:
    virtual void initialize(int stage) override;

public:
    void readCSV(const char* filename);
    cValue getRand() override;
    cValue getRand(std::string key) override {
        throw cRuntimeError("DelayReplayer does not support random number generation with a key, but %s was provided", key.c_str());
    }
    DelayReplayer();
    virtual ~DelayReplayer();
};

} /* namespace d6g */

#endif /* DISTRIBUTION_DELAYREPLAYER_DELAYREPLAYER_H_ */