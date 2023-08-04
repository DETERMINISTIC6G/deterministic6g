//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package d6g.simulations.talkertoreceiver;

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

network talkertoreceiver extends DetComNetworkBase
{
    parameters:
        
    submodules:
 		talker: TsnDevice {
            @display("p=250,200");  
        }
        bridge1: DetComAdapter {
            @display("p=350,200");
        }
        detcom: DetCom {
            @display("p=400,300");  
        }
        bridge2: DetComAdapter {
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
        
        detcom.ueg++ <--> NNIChannel <--> bridge2.ueg++;
        bridge2.ethg++ <--> EthernetLink <--> cloud.ethg++;
        
        detcom.ueg++ <--> NNIChannel <--> bridge3.ueg++;
        bridge3.ethg++ <--> EthernetLink <--> receiver.ethg++;
}

