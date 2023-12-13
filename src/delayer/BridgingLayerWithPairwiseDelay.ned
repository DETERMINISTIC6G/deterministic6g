// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.delayer;

import inet.protocolelement.contract.IProtocolLayer;
import inet.protocolelement.processing.IProcessingDelayLayer;

// This module extends INETs BridgingLayer but additionally adds our PairwiseDelayer.
module BridgingLayerWithPairwiseDelay like IProtocolLayer
{
    parameters:
        string macTableModule = default(""); // specifies the module handling the MAC address table.
        
        string interfaceTableModule; // relative module path of the interface table.
        
        *.macTableModule = default(absPath(this.macTableModule));
        *.interfaceTableModule = default(this.interfaceTableModule); 
        @display("i=block/layer");
        
    gates:
        input upperLayerIn; // Input gate for receiving packets from the upper layer (e.g., network layer).
        output upperLayerOut; // Output gate for sending packets to the upper layer.
        input lowerLayerIn; // Input gate for receiving packets from the lower layer (e.g., MAC layer).
        output lowerLayerOut; // Output gate for sending packets to the lower layer.
    submodules:
        // Layer responsible for adding delays to packet processing.
        processingDelayLayer: <default("")> like IProcessingDelayLayer {
            @display("p=300,150");
        }
        
        // Handles the direction reversal of packets.
        directionReverser: <default("DirectionReverserLayer")> like IProtocolLayer {
            @display("p=300,300");
        }
        
        // Manages stream identification operations.
        streamIdentifier: <default("")> like IProtocolLayer {
            @display("p=300,450");
        }
        
        // Responsible for relay operations on the stream.
        streamRelay: <default("")> like IProtocolLayer {
            @display("p=300,600");
        }
        
        // Applies filtering rules to the stream.
        streamFilter: <default("")> like IProtocolLayer {
            @display("p=300,750");
        }
        
        // Encodes or transforms the stream.
        streamCoder: <default("")> like IProtocolLayer {
            @display("p=300,900");
        }
        
        // Manages the relay operations at the interface level.
        interfaceRelay: <default("InterfaceRelayLayer")> like IProtocolLayer {
            @display("p=300,1050");
        }
        
        // Manages VLAN policies.
        vlanPolicy: <default("")> like IProtocolLayer {
            @display("p=300,1200");
        }
        
        // Adds delays to the packet on a pairwise basis, mainly for egress traffic.
        pairwiseDelayer: <default("ProcessingDelayLayer")> like IProcessingDelayLayer {
            @display("p=300,1350");
            ingress.typename = default("");
            egress.typename = default("PairwiseDelayer");
        }
    connections:
        upperLayerIn --> processingDelayLayer.upperLayerIn;
        processingDelayLayer.lowerLayerOut --> directionReverser.upperLayerIn;
        directionReverser.lowerLayerOut --> streamIdentifier.upperLayerIn;
        streamIdentifier.lowerLayerOut --> streamRelay.upperLayerIn;
        streamRelay.lowerLayerOut --> streamFilter.upperLayerIn;
        streamFilter.lowerLayerOut --> streamCoder.upperLayerIn;
        streamCoder.lowerLayerOut --> interfaceRelay.upperLayerIn;
        interfaceRelay.lowerLayerOut --> vlanPolicy.upperLayerIn;
        vlanPolicy.lowerLayerOut --> pairwiseDelayer.upperLayerIn;
        pairwiseDelayer.lowerLayerOut --> lowerLayerOut;

		lowerLayerIn --> pairwiseDelayer.lowerLayerIn;
        pairwiseDelayer.upperLayerOut --> vlanPolicy.lowerLayerIn;
        vlanPolicy.upperLayerOut --> interfaceRelay.lowerLayerIn;
        interfaceRelay.upperLayerOut --> streamCoder.lowerLayerIn;
        streamCoder.upperLayerOut --> streamFilter.lowerLayerIn;
        streamFilter.upperLayerOut --> streamRelay.lowerLayerIn;
        streamRelay.upperLayerOut --> streamIdentifier.lowerLayerIn;
        streamIdentifier.upperLayerOut --> directionReverser.lowerLayerIn;
        directionReverser.upperLayerOut --> processingDelayLayer.lowerLayerIn;
        processingDelayLayer.upperLayerOut --> upperLayerOut;
}
