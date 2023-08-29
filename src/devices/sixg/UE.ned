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

import inet.linklayer.ethernet.LayeredEthernetInterface;
import inet.node.tsn.TsnSwitch;
import inet.linklayer.contract.IEthernetInterface;
///This module reperesents a User Equipment(UE) and extends the behavior of 'LayeredEthernetInterface' module of INET.
///The module configures parameters related to the physical layer's inter frame gap inserter duration 
///and the communication bitrate specific to UE.
module UE extends LayeredEthernetInterface {
    parameters:
    	phyLayer.interFrameGapInserter.duration = default(0s);///inter frame gap inserter duration
    	bitrate = default(inf Mbps);///bit rate of UE communication link
}
