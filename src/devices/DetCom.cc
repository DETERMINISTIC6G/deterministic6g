// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// 

#include "DetCom.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"


namespace d6g {
using namespace inet;

Define_Module(DetCom);

void DetCom::initialize(int stage) {
    cComponent::initialize(stage);
    if (stage == INITSTAGE_NETWORK_INTERFACE_CONFIGURATION) {
        cXMLElement *configEntity = par("delayConfig");
        // parse XML config
        if (strcmp(configEntity->getTagName(), "delays") != 0) {
            throw cRuntimeError("Cannot read delay configuration, unaccepted '%s' entity at %s",
                                configEntity->getTagName(),
                                configEntity->getSourceLocation());
        }

        cXMLElementList uplinkEntities = configEntity->getChildrenByTagName("uplink");
        for (auto &uplinkEntity: uplinkEntities) {
            auto dstt = getDstt(uplinkEntity);
            dstt->par("delayUplink").parse(uplinkEntity->getNodeValue());
        }

        cXMLElementList downlinkEntities = configEntity->getChildrenByTagName("downlink");
        for (auto &downlinkEntity: downlinkEntities) {
            auto dstt = getDstt(downlinkEntity);
            dstt->par("delayDownlink").parse(downlinkEntity->getNodeValue());
        }
    }
}

cModule *DetCom::getDstt(cXMLElement *delayEntity) const {
    const char *deviceAttr = delayEntity->getAttribute("device");
    if (deviceAttr == nullptr) {
        throw cRuntimeError("Invalid delay configuration, missing 'device' attribute at %s",
                            delayEntity->getSourceLocation());
    }
    L3NetworkConfiguratorBase::Matcher deviceMatcher(deviceAttr);
    for (int i = 0; i < getSubmoduleVectorSize("dstt"); i++) {
        auto dstt = getSubmodule("dstt", i);
        if (dstt->getSubmoduleVectorSize("eth") == 0) {
            throw cRuntimeError("Invalid uplink delay configuration, no 'eth' interface found at %s",
                                dstt->getFullPath().c_str());
        }
        auto eth = dynamic_cast<NetworkInterface *>(dstt->getSubmodule("eth", 0));
        std::string deviceName = eth->getRxTransmissionChannel()->getSourceGate()->getOwnerModule()->getFullName();
        if (deviceMatcher.matches(deviceName.c_str())) {
            return dstt;
        }
    }
    throw cRuntimeError("Invalid delay configuration, no device found for '%s' at %s",
                        deviceAttr, delayEntity->getSourceLocation());
}

} /* namespace d6g */
