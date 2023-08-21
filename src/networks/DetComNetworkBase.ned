//
// Copyright (C) 2023 Deterministic 6G.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

/// \cond
package d6g.networks;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
/// \endcond

/// \class DetComNetworkBase
/// DetComNetworkBase is a new network type extending from TsnNetworkBase.
network DetComNetworkBase extends TsnNetworkBase 
{
    parameters:
        /// Setting the bitrate of all Ethernet interfaces to a default value of 100Mbps.
        /// If not explicitly defined elsewhere, the default value will be used.
        *.eth[*].bitrate = default(100Mbps);
        
        /// Enabling egress traffic shaping for all nodes in the network.
		**.hasEgressTrafficShaping = true;
		
		/// Specifying that all nodes in the network have incoming streams.
		**.hasIncomingStreams = true;
		
		/// Defining protocols which should not be reversed by the bridging direction reverser.
		**.bridging.directionReverser.reverser.excludeEncapsulationProtocols = ["ieee8021qctag"];
		
		/// Specifying the number of traffic classes at the MAC layer for all Ethernet interfaces.
		**.eth[*].macLayer.queue.numTrafficClasses = 2;
		
		/// Defining a mapping between different traffic stream types and their respective PCP values.
        /// PCP: Priority Code Point (used in VLAN tags for traffic prioritization).
		**.bridging.streamCoder.*.mapping = [{stream: "BK", pcp: 0},
									         {stream: "BE", pcp: 1},
							                 {stream: "EE", pcp: 2},
									         {stream: "CA", pcp: 3},
									         {stream: "VI", pcp: 4},
                                             {stream: "VO", pcp: 5},
                                             {stream: "IC", pcp: 6},
                                             {stream: "NV", pcp: 7}];
}