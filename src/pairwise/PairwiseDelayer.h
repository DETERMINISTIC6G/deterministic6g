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

class INET_API PairwiseDelayer : public PacketDelayerBase {
    class INET_API DelayEntry {
    public:
        explicit DelayEntry(cXMLElement *delayEntity);

        int in;
        int out;
        cDynamicExpression delay;

        ~DelayEntry() = default;
    };

private:
    std::map<int, std::map<int, DelayEntry *>> delays;

protected:
    void initialize(int stage) override;
    clocktime_t computeDelay(Packet *packet) const override;
};


} // PKDelayer

#endif /* PKDELAYER_H_ */
