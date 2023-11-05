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
// This might need some changes!
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
}