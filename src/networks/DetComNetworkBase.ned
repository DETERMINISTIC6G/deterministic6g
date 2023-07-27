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

package d6g.networks;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;

network DetComNetworkBase extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps);
		**.hasEgressTrafficShaping = true;
		**.hasIncomingStreams = true;
		
		**.bridging.directionReverser.reverser.excludeEncapsulationProtocols = ["ieee8021qctag"];
		**.eth[*].macLayer.queue.numTrafficClasses = 2;
		**.bridging.streamCoder.*.mapping = [{stream: "BK", pcp: 0},
									         {stream: "BE", pcp: 1},
							                 {stream: "EE", pcp: 2},
									         {stream: "CA", pcp: 3},
									         {stream: "VI", pcp: 4},
                                             {stream: "VO", pcp: 5},
                                             {stream: "IC", pcp: 6},
                                             {stream: "NV", pcp: 7}];
}