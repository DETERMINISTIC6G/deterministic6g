// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.devices.tsntranslator;

import inet.node.tsn.TsnSwitch;
import inet.linklayer.contract.IEthernetInterface;

// The module extends the TsnSwitch module, and provides the same functionality.
// Additionally it provides one ore multiple UE interfaces.
// See UE for more information
module TsnTranslator extends TsnSwitch
{
    parameters:
        int numTtInterfaces = default(0); // Specifies the minimum number of user equipment (UE) Ethernet interfaces that the adapter supports.
        bool isDstt = default(false); // Specifies whether the TSN Translator is a DS-TT (otherwise it is a NW-TT).
        
        volatile double delayUplink @mutable @unit(s) = default(0s); // Uplink Delay
        volatile double delayDownlink @mutable @unit(s) = default(0s); // Downlink Delay
        
        // Chooses the MAC layer type based on whether frame preemption is enabled.
        // "EthernetPreemptingMacLayer" is used for preemptive frames, otherwise "EthernetMacLayer" is used.
        tt[*].macLayer.typename = default(hasFramePreemption ? "EthernetPreemptingMacLayer" : "EthernetMacLayer");
        
        // Determines the type of queue to be used for egress traffic shaping.
        // If egress traffic shaping is enabled, "Ieee8021qTimeAwareShaper" is used.
        // Otherwise, a standard "PacketQueue" is used.
        tt[*].macLayer.queue.typename = default(hasEgressTrafficShaping ? "Ieee8021qTimeAwareShaper" : "PacketQueue"); 
        
        // Chooses the appropriate PHY layer type.
        // "EthernetStreamThroughPhyLayer" is used if cut-through switching is enabled.
        // "EthernetPreemptingPhyLayer" is used if frame preemption is enabled but cut-through is not.
        // "EthernetPhyLayer" is the default PHY layer type.
        tt[*].phyLayer.typename = default(hasCutthroughSwitching ? "EthernetStreamThroughPhyLayer" : (hasFramePreemption ? "EthernetPreemptingPhyLayer" : "EthernetPhyLayer"));

        bridging.typename = default("TTBridgingLayer");

        bridging.delayLayer.typename = default(isDstt ? "TTDelayLayer" : "");
        bridging.delayLayer.delayUplink = default(this.delayUplink);
        bridging.delayLayer.delayDownlink = default(this.delayDownlink);
    gates:
        inout ttg[numTtInterfaces] @labels(EtherFrame-conn);
    submodules:
        tt[sizeof(ttg)]: <default("TTInterface")> like IEthernetInterface {
            @display("p=325,900,row,150;q=txQueue");
        }
    connections:
        for i=0..sizeof(ttg)-1 {
            li.out++ --> tt[i].upperLayerIn;
            li.in++ <-- tt[i].upperLayerOut;
            tt[i].phys <--> { @display("m=s"); } <--> ttg[i];
        }
}
