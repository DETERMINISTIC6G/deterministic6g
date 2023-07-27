//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package d6g.simulations.baseline;

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

network Baseline extends DetComNetworkBase
{
    parameters:
        
    submodules:
        talker: TsnDevice {
            @display("p=350,200");
        }
        bridge1: TsnSwitch {
            @display("p=350,300");
        }
        bridge2: DetComAdapter  {
            @display("p=350,400");
        }
        detcom: DetCom {
            @display("p=450,400");
        }
        bridge3: DetComAdapter {
            @display("p=550,400");
        }
        bridge4: TsnSwitch {
            @display("p=550,300");
        }
        listener: TsnDevice {
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

