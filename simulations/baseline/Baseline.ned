//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package d6g.simulations.baseline;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;

import d6g.distribution.histogram.Histogram;

network Baseline extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps);
    submodules:
        histogram: Histogram;
        talker: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=350,200");
        }
        bridge1: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=350,300");
        }
        bridge2: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=350,400");
        }
        detcom: <default("DetCom")> like IEthernetNetworkNode {
            @display("p=450,400");
        }
        bridge3: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=550,400");
        }
        bridge4: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=550,300");
        }
        listener: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=550,200");
        }
    connections:
        talker.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ethg++ <--> EthernetLink <--> detcom.ethg++;
        detcom.ethg++ <--> EthernetLink <--> bridge3.ethg++;
        bridge3.ethg++ <--> EthernetLink <--> bridge4.ethg++;
        bridge4.ethg++ <--> EthernetLink <--> listener.ethg++;
}

