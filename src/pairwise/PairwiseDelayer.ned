//
// Copyright (C) 2023 Deterministic 6G.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.pairwise;

import inet.queueing.base.PacketDelayerBase;
import inet.queueing.contract.IPacketDelayer;

//
// The module is designed to delay packets based on pairwise configurations of input/output interfaces.
//
// The configuration is defined in XML format as follows:
// <pre>
// <delays>
//     <delay in="[cModule]" out="[cModule]" activateAt="[opt. cValue]">[cDynamicExpression]</delay>
//     ...
// </delays>
// </pre>
// Where in and out are the cModules connected to the in and out interface respectively.
// activateAt is the time when the delay is activated. If not specified, the delay is activated immediately.
// cFunction is the function that defines the delay. It can be a constant value or a function of time.
simple PairwiseDelayer extends PacketDelayerBase like IPacketDelayer
{
    parameters:
        xml delayConfig = default(xml("<delays></delays>")); // XML configuration definition for delay
        @class(PairwiseDelayer);
}
