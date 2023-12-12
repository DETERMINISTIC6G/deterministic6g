// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DISTRIBUTION_DELAYREPLAYER_DELAYREPLAYERCONTAINER_H_
#define DISTRIBUTION_DELAYREPLAYER_DELAYREPLAYERCONTAINER_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include "../contract/IRandomNumberProvider.h"
#include "../delayreplayer/DelayReplayer.h"

namespace d6g {

class INET_API DelayReplayerContainer : public cSimpleModule, public IRandomNumberProvider{
private:
    std::map<std::string, DelayReplayer*> delayreplayers;

protected:
    virtual void initialize(int stage) override;
    static DelayReplayer* loadDelayReplayerFromFile(const char* fileName);

public:
    DelayReplayer* getDelayreplayer(std::string key) const;
    cValue getRand() override{
        throw cRuntimeError("DelayReplayerContainer requires a key (name of delayreplayer)");
    }
    cValue getRand(std::string key) override;
    ~DelayReplayerContainer() override;
};

} /* namespace d6g */

#endif /* DISTRIBUTION_DELAYREPLAYER_DELAYREPLAYERCONTAINER_H_ */
