// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
package d6g.delayer;


import inet.queueing.base.PacketDelayerBase;
import inet.queueing.contract.IPacketDelayer;

//
// The module is designed to delay packets based on it's ingress and egress interfaces.
//
// The configuration is defined in XML format as follows:
// <pre>
// <delays>
//     <delay interface="[cModule]" direction="opt. (req|ind)" activateAt="[opt. cValue]">[cDynamicExpression]</delay>
//     ...
// </delays>
// </pre>
// Where in and out are the cModules connected to the in and out interface respectively. Alternatively you can directly specify the interface ID.
// activateAt is the time when the delay is activated. If not specified, the delay is activated immediately.
// cDynamicExpression is the function that defines the delay. It can be a constant value or a function of time (i.e. 10us or truncnormal(40us,5us))
// direction defines whether the delay is applied to incoming or outgoing packets (see mode parameter). If direction is not defined it applies to both.
// Note: If multiple delays are defined for the same interface, the latest configuration overrides previous ones.

simple TTDelayer extends PacketDelayerBase like IPacketDelayer
{
    parameters:
        volatile double delay @unit(s) = default(0s); // specifies delay per packet
        object indInterfaceTypes = default([]); // Only apply delay if the ind interface is of specific type (e.g. ["tt"] or ["tt", "eth"], empty means any)
        object reqInterfaceTypes = default([]); // Only apply delay if the req interface is of specific type (e.g. ["tt"] or ["tt", "eth"], empty means any)
        @class(TTDelayer);
}
