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
        bridge1: TsnSwitch {
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
        bridge3: TsnSwitch {
            @display("p=350,400");
        }
        receiver: TsnDevice{
            @display("p=250,400");  
        }
        
    connections:
        talker.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> NNIChannel <--> detcom.ueg++;
        detcom.ueg++ <--> NNIChannel <--> bridge2.ueg++;
        bridge2.ethg++ <--> EthernetLink <--> cloud.ethg++;
        cloud.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ueg++ <--> NNIChannel <--> detcom.ueg++;
        detcom.ueg++ <--> NNIChannel <--> bridge3.ethg++;
        bridge3.ethg++ <--> EthernetLink <--> receiver.ethg++;
}

