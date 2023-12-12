// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DETERMINISTIC6G_PAIRWISEDELAYER_H_
#define DETERMINISTIC6G_PAIRWISEDELAYER_H_

#include "inet/queueing/base/PacketDelayerBase.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"

namespace d6g {
using namespace inet;

using namespace queueing;

/**
 * PairwiseDelayer implements a delayer allowing to specify delays based on the input/output pair of interfaces.
 * For a detailed description of the module, see the NED file.
 */
class INET_API PairwiseDelayer : public PacketDelayerBase {
    static const short PAIRWISE_ACTIVATE_KIND = 3495; ///< Kind for activate message, used to distinguish from other messages

    /**!
     * DelayEntry is a class that represents a delay entry in the delayer delayer.
     */
    class INET_API DelayEntry {
    public:
        DelayEntry(cXMLElement *delayEntity, cModule *context);

        int in = -1; ///< Input interface ID
        int out = -1; ///< Output interface ID
        bool toApp = false; // determines if the packet is destined for an internal app
        bool fromApp = false; // determines if the packet is originating from an internal app.
        simtime_t activateAt = 0; ///< Time to activate the delay entry
        cDynamicExpression delay; ///< Delay expression

        ~DelayEntry() = default;

        void addInterfaceIdFromName(const cModule *context, const char *inAttr, const char *outAttr,
                                    const char *interfaceType);
    };

private:
    std::map<int, std::map<int, DelayEntry *>> delays; ///< Map of in and out interfaces to delay entries

protected:
    void initialize(int stage) override;

    /**!
     * Compute the delay for the given packet.
     * Uses the InterfaceInd and InterfaceReq tags to determine the input and output interfaces.
     *
     * @param packet Packet to delay
     * @return delay for the packet
     */
    clocktime_t computeDelay(Packet *packet) const override;

    virtual void handleMessage(cMessage *message) override;

    void activateEntry(DelayEntry *delayEntry); ///< Activate a delay entry
};


} // PairwiseDelayer

#endif /* PAIRWISEDELAYER_H_ */
