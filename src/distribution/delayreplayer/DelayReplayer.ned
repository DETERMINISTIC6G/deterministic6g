// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.distribution.delayreplayer;

simple DelayReplayer
{
    parameters:
        string csvFilename;
        @class(DelayReplayer);
        @display("i=block/delay");
}

