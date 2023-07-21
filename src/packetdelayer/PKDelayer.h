/*
 * PKDelayer.h
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

class INET_API PKDelayer // public PacketDelayerBase , public DistributionBase
{
//  protected:
//    cRNG *rng;
//    cPar *delayParameter = nullptr;
//    cPar *bitrateParameter = nullptr;
//
//  protected:
//    virtual void initialize(int stage) override;

//    virtual clocktime_t computeDelay(Packet *packet) const override;

//  public:
//    static cNEDValue ned_Static(cComponent *context, cNEDValue argv[], int argc);

};

} // PKDelayer

#endif /* PKDELAYER_H_ */
