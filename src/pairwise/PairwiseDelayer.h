/*
 * PKDelay.h
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#ifndef PAIRWISEDELAYER_H_
#define PAIRWISEDELAYER_H_

#include "inet/common/INETDefs.h"
#include "inet/queueing/base/PacketDelayerBase.h"

namespace pkdelay {
using namespace inet;

using namespace queueing;

class INET_API PairwiseDelayer : public PacketDelayerBase
{
  protected:
    cPar *delayParameter = nullptr;
    cPar *bitrateParameter = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual clocktime_t computeDelay(Packet *packet) const override;
};

} // PKDelayer

#endif /* PKDELAYER_H_ */
