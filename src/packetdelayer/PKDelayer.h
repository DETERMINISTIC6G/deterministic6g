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
#include "../distribution/DistributionBase.h"

namespace pkdelay {
using namespace inet;

using namespace queueing;

class INET_API PKDelayer : public PacketDelayerBase , public DistributionBase
{
  protected:
    cPar *delayParameter = nullptr;
    cPar *delayLB = nullptr;
    cPar *delayUB = nullptr;
    cPar *mean = nullptr;
    cPar *stddev = nullptr;
    cPar *bitrateParameter = nullptr;
    mutable double delayTime = 0; // or declare clocktime_t delayTime
    cHistogram *delayStats; // Declare cHistogram object

  protected:
    virtual void initialize(int stage) override;

    /* ---------------------------- Random Delay Time ---------------------------- */
    // Method 1
    virtual double GetRandNum(double LowerBound, double UpperBound) const override;
    // Method 2
    virtual double ArbitraryDelayTime(double mean, double stddev) const override;
    /* --------------------------------------------------------------------------- */
    virtual clocktime_t computeDelay(Packet *packet) const override;

// For creating a histogram below -----------------------------------------------
    virtual void finish() override; // Add finish method to record the histogram

  public:
    virtual ~PKDelayer(); // Add destructor declaration
// ------------------------------------------------------------------------------

};

} // PKDelayer

#endif /* PKDELAYER_H_ */
