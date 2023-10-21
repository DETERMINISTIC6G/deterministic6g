//
// Copyright (C) 2023 Deterministic 6G.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.networks;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;

//
// This network extends the TsnNetworkBase but predefines some parameters.
//
network DetComNetworkBase extends TsnNetworkBase 
{
    parameters:
        // Setting the bitrate of all Ethernet interfaces to a default value of 100Mbps.
        // If not explicitly defined elsewhere, the default value will be used.
        *.eth[*].bitrate = default(1Gbps);
        
        
		**.hasEgressTrafficShaping = true; // Enabling egress traffic shaping for all nodes in the network.
		
		
		**.hasIncomingStreams = true; // Specifying that all nodes in the network have incoming streams.
		
		
		**.bridging.directionReverser.reverser.excludeEncapsulationProtocols = ["ieee8021qctag"]; // Defining protocols which should not be reversed by the bridging direction reverser.
		
		
		**.eth[*].macLayer.queue.numTrafficClasses = 2; // Specifying the number of traffic classes at the MAC layer for all Ethernet interfaces.
		
		// Defining a mapping between different traffic stream types and their respective PCP values.
        // PCP: Priority Code Point (used in VLAN tags for traffic prioritization).
		**.bridging.streamCoder.*.mapping = [{stream: "BK", pcp: 0},
									         {stream: "BE", pcp: 1},
							                 {stream: "EE", pcp: 2},
									         {stream: "CA", pcp: 3},
									         {stream: "VI", pcp: 4},
                                             {stream: "VO", pcp: 5},
                                             {stream: "IC", pcp: 6},
                                             {stream: "NV", pcp: 7}];
}