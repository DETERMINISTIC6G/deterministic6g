// 
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.devices.sixg;

import inet.node.ethernet.EthernetLink;

//
// This module represents a Ethernet communication channel with specific attributes such as channel length and data rate.
// Extending the capabilities of the 'EthernetLink' module from INET ,it provides a enhanced framework for network simulations 
//
channel NNIChannel extends EthernetLink {
    length = default(0m); // length of channel
    datarate = 0bps; // data transmission rate
    @display("ls=,,da");
}
