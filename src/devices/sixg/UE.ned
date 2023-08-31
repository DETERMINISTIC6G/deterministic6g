// 
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.devices.sixg;

import inet.linklayer.ethernet.LayeredEthernetInterface;
import inet.node.tsn.TsnSwitch;
import inet.linklayer.contract.IEthernetInterface;

//
// This module reperesents a User Equipment(UE) and extends the behavior of 'LayeredEthernetInterface' module of INET.
// The module configures parameters related to the physical layer's inter frame gap inserter duration 
// and the communication bitrate specific to UE.
//
module UE extends LayeredEthernetInterface {
    parameters:
    	phyLayer.interFrameGapInserter.duration = default(0s); // duration of the inter frame gap inserter 
    	bitrate = default(inf Mbps); // bitrate of UE communication link
}
