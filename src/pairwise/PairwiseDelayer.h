/*
 * PairwiseDelayer.h
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#ifndef DETERMINISTIC6G_PAIRWISEDELAYER_H_
#define DETERMINISTIC6G_PAIRWISEDELAYER_H_

#include "inet/queueing/base/PacketDelayerBase.h"

namespace d6g {
using namespace inet;

using namespace queueing;

class INET_API PairwiseDelayer : public PacketDelayerBase {
    static const short PAIRWISE_ACTIVATE_KIND = 3495;

    class INET_API DelayEntry {
    public:
        DelayEntry(cXMLElement *delayEntity, cModule *context);

        int in = -1;
        int out = -1;
        simtime_t activateAt = 0;
        cDynamicExpression delay;

        ~DelayEntry() = default;
    };

private:
    std::map<int, std::map<int, DelayEntry *>> delays;

protected:
    void initialize(int stage) override;
    clocktime_t computeDelay(Packet *packet) const override;
    virtual void handleMessage(cMessage *message) override;
    void activateEntry(DelayEntry *delayEntry);
};


} // PairwiseDelayer

#endif /* PAIRWISEDELAYER_H_ */
