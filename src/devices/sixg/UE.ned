// 
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.devices.sixg;

import inet.linklayer.ethernet.LayeredEthernetInterface;
import inet.node.tsn.TsnSwitch;
import inet.linklayer.contract.IEthernetInterface;

// The simulation approach followed in this project uses given delay distributions to simulate wireless behavior.
// The underlying simulation model is still based on INETs wired Ethernet communication.
//
// To this end, the gNB <-> UE communication is modelled using the PairwiseDelayer module within the DetCom node.
// However, we don't want any further delays to be introduced by the underlying wired Ethernet communication in the simulation framework.
// Thus, we provide a UE interface with the same functionality as the LayeredEthernetInterface, but without additional delays.
// The UE interface shall be connected to another UE interface using the optimal UEChannel.
//
// In the future, this UE interface might add additional functionality to further implement wireless behavior.
module UE extends LayeredEthernetInterface {
    parameters:
    	phyLayer.interFrameGapInserter.duration = default(0s); // duration of the inter frame gap inserter 
    	bitrate = default(inf Mbps); // bitrate of UE communication link
}
