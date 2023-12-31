// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.devices.sixg;

import inet.node.tsn.TsnSwitch;
import inet.linklayer.contract.IEthernetInterface;

// The module extends the TsnSwitch module, and provides the same functionality.
// Additionally it provides one ore multiple UE interfaces.
// See UE for more information
module UETsnSwitch extends TsnSwitch
{
    parameters:
        int numUeInterfaces = default(0); // Specifies the minimum number of user equipment (UE) Ethernet interfaces that the adapter supports.
        
        // Chooses the MAC layer type based on whether frame preemption is enabled.
        // "EthernetPreemptingMacLayer" is used for preemptive frames, otherwise "EthernetMacLayer" is used.
        ue[*].macLayer.typename = default(hasFramePreemption ? "EthernetPreemptingMacLayer" : "EthernetMacLayer");
        
        // Determines the type of queue to be used for egress traffic shaping.
        // If egress traffic shaping is enabled, "Ieee8021qTimeAwareShaper" is used.
        // Otherwise, a standard "PacketQueue" is used.
        ue[*].macLayer.queue.typename = default(hasEgressTrafficShaping ? "Ieee8021qTimeAwareShaper" : "PacketQueue"); 
        
        // Chooses the appropriate PHY layer type.
        // "EthernetStreamThroughPhyLayer" is used if cut-through switching is enabled.
        // "EthernetPreemptingPhyLayer" is used if frame preemption is enabled but cut-through is not.
        // "EthernetPhyLayer" is the default PHY layer type.
        ue[*].phyLayer.typename = default(hasCutthroughSwitching ? "EthernetStreamThroughPhyLayer" : (hasFramePreemption ? "EthernetPreemptingPhyLayer" : "EthernetPhyLayer")); 
    gates:
        inout ueg[numUeInterfaces] @labels(EtherFrame-conn);
    submodules:
        ue[sizeof(ueg)]: <default("UE")> like IEthernetInterface {
            @display("p=325,900,row,150;q=txQueue");
        }
    connections:
        for i=0..sizeof(ueg)-1 {
            li.out++ --> ue[i].upperLayerIn;
            li.in++ <-- ue[i].upperLayerOut;
            ue[i].phys <--> { @display("m=s"); } <--> ueg[i];
        }
}
