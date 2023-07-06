/*
 * PKDelay.h
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#ifndef PKDELAYER_H_
#define PKDELAYER_H_

#include "inet/common/INETDefs.h"
#include "inet/queueing/base/PacketDelayerBase.h"

namespace pkdelay {
using namespace inet;

using namespace queueing;

class INET_API PKDelayer : public PacketDelayerBase
{
  protected:
    cPar *delayParameter = nullptr;
    cPar *delayLB = nullptr;
    cPar *delayUB = nullptr;
    cPar *bitrateParameter = nullptr;
    mutable double tmp_rand = 0;

  protected:
    virtual void initialize(int stage) override;
    virtual clocktime_t computeDelay(Packet *packet) const override;
};

} // PKDelayer

#endif /* PKDELAYER_H_ */
