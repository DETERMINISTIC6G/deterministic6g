// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.simulations.edgecloud;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
import d6g.devices.sixg.DetCom;
import d6g.devices.sixg.UETsnDevice;
import d6g.devices.sixg.UEChannel;
import d6g.networks.DetComNetworkBase;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;
import ned.DatarateChannel;
import d6g.distribution.histogram.Histogram;
import d6g.distribution.histogram.HistogramContainer;

// 
// The module extends from DetComNetworkBase. This network is meant to simulate deterministic communications in an edge cloud setting. 
// 
network EdgeCloudNetwork extends DetComNetworkBase
{
    parameters:
   
    submodules:
        histogramContainer:HistogramContainer{
            @display("p=100,800;is=s");
        }
 		talker: UETsnDevice {
            @display("p=300,200");  
        }
        detcom: DetCom {
            @display("p=400,300");  
        }
        cloudServer: TsnDevice {
            @display("p=600,300");  
        }
        bridge: TsnSwitch {
            @display("p=500,300");
        }
        receiver: UETsnDevice {
            @display("p=300,400");  
        }
        
    connections:
        talker.ueg++ <--> UEChannel <--> detcom.ueg++;
        
        detcom.ethg++ <--> EthernetLink <--> bridge.ethg++;
        bridge.ethg++ <--> EthernetLink <--> cloudServer.ethg++;
        
        detcom.ueg++ <--> UEChannel <--> receiver.ueg++;
}
