//
// Copyright (C) 2023 Deterministic 6G.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

/// \cond
package d6g.apps.edgecloud;

import inet.applications.udpapp.UdpEchoApp;
/// \endcond

/// \class UdpEdgeCloudApp
/// The UdpEdgeCloudApp module is designed to simulate a UDP-based application in edge cloud scenarios.
/// This module builds upon the UdpEchoApp, inheriting its functionalities and adding the capability
/// to introduce specific delays. Such delays might be used to simulate various network conditions
/// or service latencies in edge cloud settings. Users can specify destination addresses, destination 
/// ports, and custom delays to simulate application behavior in edge environments.
simple UdpEdgeCloudApp extends UdpEchoApp {
    parameters:
        @class(UdpEdgeCloudApp);
        
        /// destination IP address for the UDP packets
        string destAddress = default(""); 
        
        /// destination port number for the UDP packets
        int destPort; 
        
        /// specifies delay per UDP packets
        volatile double delay @unit(s) = default(0s); 
}
