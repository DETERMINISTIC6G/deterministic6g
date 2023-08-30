//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.simulations.edgecloud;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
import d6g.devices.sixg.DetCom;
import d6g.devices.sixg.DetComAdapter;
import d6g.devices.sixg.NNIChannel;
import d6g.networks.DetComNetworkBase;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;
import ned.DatarateChannel;
import d6g.distribution.histogram.Histogram;

// 
// The module extends from DetComNetworkBase. This network is meant to simulate deterministic communications in an edge cloud setting. 
// 
network EdgeCloudNetwork extends DetComNetworkBase
{
    parameters:
   
    submodules:
        histogram: Histogram {
            @display("p=100,400;is=s");
        }
 		talker: TsnDevice {
            @display("p=250,200");  
        }
        bridge1: DetComAdapter {
            @display("p=350,200");
        }
        detcom: DetCom {
            @display("p=400,300");  
        }
        bridge2: TsnSwitch {
            @display("p=500,300");
        }
        cloud: TsnDevice {
            @display("p=600,300");  
        }
        bridge3: DetComAdapter {
            @display("p=350,400");
        }
        receiver: TsnDevice{
            @display("p=250,400");  
        }
        
    connections:
        talker.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ueg++ <--> NNIChannel <--> detcom.ueg++;
        
        detcom.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ethg++ <--> EthernetLink <--> cloud.ethg++;
        
        detcom.ueg++ <--> NNIChannel <--> bridge3.ueg++;
        bridge3.ethg++ <--> EthernetLink <--> receiver.ethg++;
}
