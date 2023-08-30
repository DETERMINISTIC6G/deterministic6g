// 
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package d6g.devices.sixg;

import inet.node.tsn.TsnSwitch;

//
// This module depicts a simulated network device involved in communication.
// It defines specific parameters which provide bridging mechanism. 
//
module DetCom extends DetComAdapter
{
    parameters:
        bridging.typename = default("BridgingLayerWithPairwiseDelay"); // type of bridging layer
        @display("i=device/antennatower");
}
