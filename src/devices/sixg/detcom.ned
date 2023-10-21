//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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
