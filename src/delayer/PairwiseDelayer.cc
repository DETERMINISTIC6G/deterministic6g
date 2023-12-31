// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "PairwiseDelayer.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"

namespace d6g {

using namespace inet;
using namespace queueing;
using namespace inet::xmlutils;


/// This is for PairwiseDelayer
Define_Module(PairwiseDelayer);

void PairwiseDelayer::initialize(int stage) {
    PacketDelayerBase::initialize(stage);
    if (stage == INITSTAGE_LAST) {
        cXMLElement *configEntity = par("delayConfig");
        // parse XML config
        if (strcmp(configEntity->getTagName(), "delays") != 0) {
            throw cRuntimeError("Cannot read delay configuration, unaccepted '%s' entity at %s",
                                configEntity->getTagName(),
                                configEntity->getSourceLocation());
        }

        cXMLElementList delayEntities = configEntity->getChildrenByTagName("delay");
        for (auto &delayEntity: delayEntities) {
            auto *delayEntry = new DelayEntry(delayEntity, getContainingNode(this));
            if (delayEntry->activateAt > 0) {
                EV << "PairwiseDelayer: Activate DelayEntry at " << delayEntry->activateAt << endl;
                auto *activateDelayEntry = new cMessage();
                activateDelayEntry->setKind(PAIRWISE_ACTIVATE_KIND);
                activateDelayEntry->setContextPointer(delayEntry);
                scheduleAt(delayEntry->activateAt, activateDelayEntry);
            } else {
                activateEntry(delayEntry);
            }
        }
    }
}

void PairwiseDelayer::activateEntry(PairwiseDelayer::DelayEntry *delayEntry) {// Check if out already in map
    EV << "PairwiseDelayer: Activate Entry" << endl;
    EV << "  in: " << delayEntry->in << endl;
    EV << "  out: " << delayEntry->out << endl;
    EV << "  delay: " << delayEntry->delay.str() << endl;
    if (delays.find(delayEntry->out) == delays.end()) {
        // If not, add it
        delays[delayEntry->out] = std::map<int, DelayEntry *>();
    }

    // Add delayEntry to map
    delays[delayEntry->out][delayEntry->in] = delayEntry;
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

    EV << "PairwiseDelayer:" << endl;

    // Select outInterfaceID from delays, otherwise select entry for -1
    auto outInterfaceDelays = delays.find(outInterfaceID);
    if (outInterfaceDelays == delays.end()) {
        outInterfaceDelays = delays.find(-1);
        if (outInterfaceDelays == delays.end()) {
            EV << "  No delay found for outInterfaceID: " << outInterfaceID << endl;
            return 0;
        }
    }


    auto outInterfaceMap = outInterfaceDelays->second;
    // Select inInterfaceID from outInterfaceMap, otherwise select entry for -1
    auto delayEntry = outInterfaceMap.find(inInterfaceID);
    if (delayEntry == outInterfaceMap.end()) {
        delayEntry = outInterfaceMap.find(-1);
        if (delayEntry == outInterfaceMap.end()) {
            EV << "  No delay found for inInterfaceID: " << inInterfaceID << endl;
            return 0;
        }
    }

    auto delayPar = delayEntry->second->delay;
    auto context = getContainingNode(this);
    auto delay = delayPar.doubleValue(context, "s");


    EV << "  inInterfaceID: " << inInterfaceID << " machted to " << delayEntry->second->in << endl;
    EV << "  outInterfaceID: " << outInterfaceID << " machted to " << delayEntry->second->out << endl;
    EV << "  delay: " << delay << " from config " << delayPar.str() << endl;

    return delay;
}

void PairwiseDelayer::handleMessage(cMessage *message) {
    if (message->getKind() == PAIRWISE_ACTIVATE_KIND) {
        auto *delayEntry = static_cast<DelayEntry *>(message->getContextPointer());
        activateEntry(delayEntry);
        delete message;
    } else {
        PacketDelayerBase::handleMessage(message);
    }
}

PairwiseDelayer::DelayEntry::DelayEntry(cXMLElement *delayEntity, cModule *context) {
    const char *inAttr = delayEntity->getAttribute("in");
    const char *outAttr = delayEntity->getAttribute("out");
    const char *activateAtAttr = delayEntity->getAttribute("activateAt");
    const char *delayAttr = delayEntity->getNodeValue();

    // --------------------- For Time Sync ---------------------
//    const char *toAppAttr = delayEntity->getAttribute("toApp");
//    if (toAppAttr != nullptr && strcmp(toAppAttr, "true") == 0) {
//        toApp = true;
//    }
//    EV << toApp << endl;
//
//    const char *fromAppAttr = delayEntity->getAttribute("fromApp");
//    if (fromAppAttr != nullptr && strcmp(fromAppAttr, "true") == 0) {
//        fromApp = true;
//    }
//    EV << fromApp << endl;
    // --------------------- ------------- ---------------------

    addInterfaceIdFromName(context, inAttr, outAttr, "eth");
    addInterfaceIdFromName(context, inAttr, outAttr, "ue");

    try {
        if (inAttr != nullptr && in == -1) {
            // Convert inAttr to an int
            std::string inAttrString(inAttr);
            in = std::stoi(inAttrString);
        }

        if (outAttr != nullptr && out == -1) {
            // Convert outAttr to an int
            std::string outAttrString(outAttr);
            out = std::stoi(outAttrString);
        }
    } catch (std::exception &e) {
        throw cRuntimeError("parser error '%s' in 'in' or 'out' attribute of '%s' entity at %s\n"
                            "No attribute or interface id called %s found", e.what(),
                            delayEntity->getTagName(), delayEntity->getSourceLocation(), inAttr);
    }

    if (activateAtAttr != nullptr) {
        // Get doublevalue from activateAtAttr using omnet++ expression
        cDynamicExpression activateAtPar = cDynamicExpression();
        activateAtPar.parse(activateAtAttr);
        cValue activateAtVal = activateAtPar.evaluate(context);
        activateAt = activateAtVal.doubleValueInUnit("s");
    }

    try {
        this->delay.parse(delayAttr);
    }
    catch (std::exception &e) {
        throw cRuntimeError("parser error '%s' in 'delay' attribute of '%s' entity at %s", e.what(),
                            delayEntity->getTagName(), delayEntity->getSourceLocation());
    }
}

void PairwiseDelayer::DelayEntry::addInterfaceIdFromName(const cModule *context, const char *inAttr,
                                                         const char *outAttr, const char *interfaceType) {
    // Check if context has submodule with name interfaceType
    if (!context->hasSubmoduleVector(interfaceType)) {
        return;
    }

    L3NetworkConfiguratorBase::Matcher inMatcher(inAttr);
    L3NetworkConfiguratorBase::Matcher outMatcher(outAttr);

    for (int i = 0; i < context->getSubmoduleVectorSize(interfaceType); i++) {
        auto *eth = dynamic_cast<NetworkInterface *>(context->getSubmodule(interfaceType, i));
        std::string name = eth->getRxTransmissionChannel()->getSourceGate()->getOwnerModule()->getFullName();
        if (inAttr != nullptr && inMatcher.matches(name.c_str())) {
            in = eth->getInterfaceId();
        }
        if (outAttr != nullptr && outMatcher.matches(name.c_str())) {
            out = eth->getInterfaceId();
        }
    }
}
}//namespace pairwisedelayer
