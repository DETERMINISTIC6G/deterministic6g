// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.devices.sixg;

import inet.node.tsn.TsnDevice;
import inet.linklayer.contract.IEthernetInterface;

// The module extends the TsnDevice module, and provides the same functionality.
// Additionally it provides one ore multiple UE interfaces.
// See UE for more information
module UETsnDevice extends TsnDevice
{
    parameters:
        int numUeInterfaces = default(0); // Specifies the minimum number of user equipment (UE) Ethernet interfaces that the adapter supports.
        
        ue[*].typename = default("UE"); // switch to modular Ethernet interface
        ue[*].macLayer.typename = default(hasFramePreemption ? "EthernetPreemptingMacLayer" : "EthernetMacLayer");
        ue[*].macLayer.queue.typename = default(hasEgressTrafficShaping ? "Ieee8021qTimeAwareShaper" : (hasFramePreemption ? "" : "PacketQueue")); // use priority queue having multiple subqueues controlled by separate gates
        ue[*].phyLayer.typename = default(hasCutthroughSwitching ? "EthernetStreamingPhyLayer" : (hasFramePreemption ? "EthernetPreemptingPhyLayer" : "EthernetPhyLayer")); // use packet streaming when cut-through switching is enabled
    gates:
        inout ueg[numUeInterfaces] @labels(EtherFrame-conn);
    submodules:
        ue[sizeof(ueg)]: <default("UE")> like IEthernetInterface {
            @display("p=825,1025,row,150;q=txQueue");
        }
    connections:
        for i=0..sizeof(ueg)-1 {
            li.out++ --> ue[i].upperLayerIn;
            li.in++ <-- ue[i].upperLayerOut;
            ue[i].phys <--> { @display("m=s"); } <--> ueg[i];
        }
}
