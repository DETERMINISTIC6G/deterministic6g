//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.simulations.baseline;

import d6g.devices.sixg.DetCom;
import d6g.devices.sixg.UEChannel;
import d6g.devices.sixg.UETsnDevice;
import d6g.devices.sixg.UETsnSwitch;
import d6g.distribution.histogram.Histogram;
import d6g.networks.DetComNetworkBase;
import inet.node.ethernet.EthernetLink;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;


//
// Base network for Baseline scenario.
// Includes two histograms, one for uplink and one for downlink.
network BaselineBase extends DetComNetworkBase
{
    submodules:
        histogramUplink: Histogram {
            @display("p=100,800");
        }
        histogramDownlink: Histogram {
            @display("p=100,900");
        }
}


network BaselineWirelessDeviceWirelessBridge extends BaselineBase
{
    parameters:

    submodules:
        device1: UETsnDevice {
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        bridge3: UETsnSwitch { // A DetCom Adapter.
            @display("p=550,400");
        }
        bridge4: TsnSwitch { // A TSN switch with a bridge function.
            @display("p=550,300");
        }
        device2: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,200");
        }
    connections:
        device1.ueg++ <--> UEChannel <--> detcom.ueg++;
        detcom.ueg++ <--> UEChannel <--> bridge3.ueg++;
        bridge3.ethg++ <--> EthernetLink <--> bridge4.ethg++;
        bridge4.ethg++ <--> EthernetLink <--> device2.ethg++;
}

network BaselineWirelessDeviceWirelessDevice extends BaselineBase
{
    parameters:

    submodules:
        device1: UETsnDevice {
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        device2: UETsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,400");
        }
    connections:
        device1.ueg++ <--> UEChannel <--> detcom.ueg++;
        detcom.ueg++ <--> UEChannel <--> device2.ueg++;
}

network BaselineWirelessBridgeWirelessBridge extends BaselineBase
{
    parameters:

    submodules:
        device1: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=350,200");
        }
        bridge1: UETsnSwitch {
            @display("p=350,300");
        }
        bridge2: UETsnSwitch {
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        bridge3: UETsnSwitch { // A DetCom Adapter.
            @display("p=550,400");
        }
        bridge4: TsnSwitch { // A TSN switch with a bridge function.
            @display("p=550,300");
        }
        device2: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,200");
        }
    connections:
        device1.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ueg++ <--> UEChannel <--> detcom.ueg++;
        detcom.ueg++ <--> UEChannel <--> bridge3.ueg++;
        bridge3.ethg++ <--> EthernetLink <--> bridge4.ethg++;
        bridge4.ethg++ <--> EthernetLink <--> device2.ethg++;
}

network BaselineWirelessDeviceWiredBridge extends BaselineBase
{
    parameters:

    submodules:
        device1: UETsnDevice {
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
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
        device1.ueg++ <--> UEChannel <--> detcom.ueg++;
        detcom.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ethg++ <--> EthernetLink <--> device2.ethg++;
}

network BaselineWirelessBridgeWiredBridge extends BaselineBase
{
    parameters:

    submodules:
        device1: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=350,200");
        }
        bridge1: UETsnSwitch {
            @display("p=350,300");
        }
        bridge2: UETsnSwitch {
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        bridge3: TsnSwitch { // A DetCom Adapter.
            @display("p=550,400");
        }
        bridge4: TsnSwitch { // A TSN switch with a bridge function.
            @display("p=550,300");
        }
        device2: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,200");
        }
    connections:
        device1.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ueg++ <--> UEChannel <--> detcom.ueg++;
        detcom.ethg++ <--> EthernetLink <--> bridge3.ethg++;
        bridge3.ethg++ <--> EthernetLink <--> bridge4.ethg++;
        bridge4.ethg++ <--> EthernetLink <--> device2.ethg++;
}

network BaselineWirelessDeviceWiredDevice extends BaselineBase
{
    parameters:

    submodules:
        device1: UETsnDevice {
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        device2: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,400");
        }
    connections:
        device1.ueg++ <--> UEChannel <--> detcom.ueg++;
        detcom.ethg++ <--> EthernetLink <--> device2.ethg++;
}

network BaselineWirelessBridgeWiredDevice extends BaselineBase
{
    parameters:

    submodules:
        device1: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=350,200");
        }
        bridge1: UETsnSwitch {
            @display("p=350,300");
        }
        bridge2: UETsnSwitch {
            @display("p=350,400");
        }
        detcom: DetCom { // DetCom module (deterministic communication).
            @display("p=450,400");
        }
        device2: TsnDevice { // A TSN device acting as a talker (data sender).
            @display("p=550,400");
        }
    connections:
        device1.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ueg++ <--> UEChannel <--> detcom.ueg++;
        detcom.ethg++ <--> EthernetLink <--> device2.ethg++;
}
