// 
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.devices.sixg;

import inet.node.ethernet.EthernetLink;

// A perfect channel, see UE for more details.
channel UEChannel extends EthernetLink {
    length = default(0m); // length of channel
    datarate = 0bps; // data transmission rate
    @display("ls=,,da");
}
