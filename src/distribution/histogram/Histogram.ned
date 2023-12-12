// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.distribution.histogram;

//
// This module provides an interface to read Histograms from XML files.
// It can be used to generate random numbers following the distribution of this interface using the IRandomNumberProvider interface.
//
// <pre>
// File format:
// <histogram>
//     <bin low="[lower bound of type cValue]"/>[count: int]</bin>
//     ...
// </histogram>
// </pre>
simple Histogram
{
    parameters:
        xml histogramConfig = default(xml("<histogram></histogram>"));
        @class(Histogram);
        @display("i=block/delay");
}
