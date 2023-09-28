//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.simulations.baseline;

import d6g.devices.sixg.DetCom;
import d6g.devices.sixg.DetComAdapter;
import d6g.devices.sixg.NNIChannel;
import d6g.networks.DetComNetworkBase;
import inet.node.ethernet.EthernetLink;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;
import inet.queueing.common.PacketDelayer;


//
// The network is to evaluate the data communication from a talker (sender) through multiple 
// bridges and adapters to a listener (receiver). It Involves both Time-Sensitive Networking (TSN) and Deterministic 
// Communication (DetCom) elements. 
//
network Baseline extends DetComNetworkBase
{
    parameters:

    submodules:
        talker: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=350,200");
        }
        bridge1: TsnSwitch { // A TSN switch with a bridge function.
            @display("p=350,300");
        }
        bridge2: DetComAdapter { // A DetCom Adapter.
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        bridge3: DetComAdapter { // A DetCom Adapter.
            @display("p=550,400");
        }
        bridge4: TsnSwitch { // A TSN switch with a bridge function.
            @display("p=550,300");
        }
        listener: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,200");
        }
    connections:
        talker.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ueg++ <--> NNIChannel <--> detcom.ueg++;
        detcom.ueg++ <--> NNIChannel <--> bridge3.ueg++;
        bridge3.ethg++ <--> EthernetLink <--> bridge4.ethg++;
        bridge4.ethg++ <--> EthernetLink <--> listener.ethg++;
}

