// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.devices.sixg;

import inet.node.tsn.TsnSwitch;

// The DetCom node is used to simulate 6G behavior by providing a given delay distribution (e.g. from real world measurements)
// This behavior is implemented in the BridgingLayerWithPairwiseDelay module.
//
// Besides the delay distribution, the DetCom node provides the same functionality as a TsnSwitch.
module DetCom extends UETsnSwitch
{
    parameters:
        bridging.typename = default("BridgingLayerWithPairwiseDelay"); // type of bridging layer
        @display("i=device/antennatower");
}
