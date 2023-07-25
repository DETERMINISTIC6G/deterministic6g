/*
 * pkDelay.cc
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#include "PairwiseDelayer.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/common/XMLUtils.h"

#include <omnetpp.h>

namespace pkdelay {

using namespace inet;
using namespace queueing;
using namespace inet::xmlutils;

Define_Module(PairwiseDelayer);

void PairwiseDelayer::initialize(int stage) {
    PacketDelayerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        cXMLElement *configEntity = par("delayConfig");
        // parse XML config
        if (strcmp(configEntity->getTagName(), "delays") != 0) {
            throw cRuntimeError("Cannot read delay configuration, unaccepted '%s' entity at %s",
                                configEntity->getTagName(),
                                configEntity->getSourceLocation());
        }

        cXMLElementList delayEntitites = configEntity->getChildrenByTagName("delay");
        for (auto &delayEntity: delayEntitites) {
            auto *delayEntry = new DelayEntry(delayEntity);
            // Check if out already in map
            if (delays.find(delayEntry->out) == delays.end()) {
                // If not, add it
                delays[delayEntry->out] = std::map<int, DelayEntry *>();
            }
            // Add delayEntry to map
            delays[delayEntry->out][delayEntry->in] = delayEntry;
        }
    }
}

clocktime_t PairwiseDelayer::computeDelay(Packet *packet) const {
    auto inInterface = packet->findTag<InterfaceInd>();
    int inInterfaceID = -1;
    if (inInterface != nullptr)
        inInterfaceID = inInterface->getInterfaceId();

    auto outInterface = packet->findTag<InterfaceReq>();
    int outInterfaceID = -1;
    if (outInterface != nullptr)
        outInterfaceID = outInterface->getInterfaceId();

    EV << "Incoming interface id is " << inInterfaceID << "; outgoing interface id is " << outInterfaceID << endl;

    // TODO: implement pairwise delay

    // Select outInterfaceID from delays, otherwise select entry for -1
    auto outInterfaceDelays = delays.find(outInterfaceID);
    if (outInterfaceDelays == delays.end()) {
        outInterfaceDelays = delays.find(-1);
        if (outInterfaceDelays == delays.end()) {
            return 0;
        }
    }


    auto outInterfaceMap = outInterfaceDelays->second;
    // Select inInterfaceID from outInterfaceMap, otherwise select entry for -1
    auto delayEntry = outInterfaceMap.find(inInterfaceID);
    if (delayEntry == outInterfaceMap.end()) {
        delayEntry = outInterfaceMap.find(-1);
        if (delayEntry == outInterfaceMap.end()) {
            return 0;
        }
    }

    auto delayPar = delayEntry->second->delay;
    auto context = getContainingNode(this);
    auto delay = delayPar.doubleValue(context, "s");

    return delay;
}

PairwiseDelayer::DelayEntry::DelayEntry(cXMLElement *delayEntity) {

    const char *inAttr = delayEntity->getAttribute("in");
    const char *outAttr = delayEntity->getAttribute("out");
    const char *delayAttr = delayEntity->getNodeValue();

    if (inAttr == nullptr) {
        in = -1;
    } else {
        // Convert inAttr to an int
        std::string inAttrString(inAttr);
        in = std::stoi(inAttrString);
    }

    if (outAttr == nullptr) {
        out = -1;
    } else {
        // Convert outAttr to an int
        std::string outAttrString(outAttr);
        out = std::stoi(outAttrString);
    }

    try {
        this->delay.parse(delayAttr);
    }
    catch (std::exception &e) {
        throw cRuntimeError("parser error '%s' in 'delay' attribute of '%s' entity at %s", e.what(),
                            delayEntity->getTagName(), delayEntity->getSourceLocation());
    }
}
}//namespace pairwisedelayer
