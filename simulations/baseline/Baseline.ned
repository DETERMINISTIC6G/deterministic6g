// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.simulations.baseline;

import d6g.devices.DetCom;
import d6g.devices.tsntranslator.TTChannel;
import d6g.devices.tsntranslator.TsnTranslator;
import d6g.distribution.histogram.Histogram;
import d6g.distribution.histogram.HistogramContainer;
import d6g.networks.DetComNetworkBase;
import inet.node.ethernet.EthernetLink;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;


// Base network for Baseline scenario.
// Includes a HistogramContainer.
network Baseline extends DetComNetworkBase
{
    submodules:
        histogramContainer: HistogramContainer{
            @display("p=100,800");
        }
        device1: TsnDevice {
            @display("p=350,400");
        }
        detCom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        bridge1: TsnSwitch { // A DetCom Adapter.
            @display("p=550,400");
        }
        bridge2: TsnSwitch { // A TSN switch with a bridge function.
            @display("p=550,300");
        }
        device2: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,200");
        }
    connections:
        device1.ethg++ <--> EthernetLink <--> detCom.dsttg++;
        detCom.nwttg <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ethg++ <--> EthernetLink <--> device2.ethg++;
}
