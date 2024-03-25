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
import d6g.devices.DetCom;
import d6g.devices.tsntranslator.TTInterface;
import d6g.devices.tsntranslator.TTChannel;
import d6g.devices.tsntranslator.TsnTranslator;
import d6g.networks.DetComNetworkBase;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;
import ned.DatarateChannel;
import d6g.distribution.histogram.Histogram;
import d6g.distribution.histogram.HistogramContainer;

// 
// The network is used to showcase our UdpEdgeCloudApp.
// 
network EdgeCloudNetwork extends DetComNetworkBase
{
    parameters:
   
    submodules:
        histogramContainer:HistogramContainer{
            @display("p=100,800;is=s");
        }
 		talker: TsnDevice {
            @display("p=300,200");  
        }
        detCom: DetCom {
            @display("p=400,300");  
        }
        cloudServer: TsnDevice {
            @display("p=600,300");  
        }
        bridge: TsnSwitch {
            @display("p=500,300");
        }
        receiver: TsnDevice {
            @display("p=300,400");  
        }
        
    connections:
        talker.ethg++ <--> EthernetLink <--> detCom.dsttg++;
        
        detCom.nwttg <--> EthernetLink <--> bridge.ethg++;
        bridge.ethg++ <--> EthernetLink <--> cloudServer.ethg++;
        
        detCom.dsttg++ <--> EthernetLink <--> receiver.ethg++;
}
