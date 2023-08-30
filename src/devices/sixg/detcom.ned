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
//DetCom extends the DetComAdapter module.
//This module depicts a simulated network device involved in communication.
//It defines specific parameters which provide bridging mechanism.
module DetCom extends DetComAdapter
{
    parameters:
        bridging.typename = default("BridgingLayerWithPairwiseDelay");/// type of bridging layer
        @display("i=device/antennatower");
}
