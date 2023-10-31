package d6g.distribution.histogram;

//
// This module provides an interface to read Histograms from XML files.
// It can be used to generate random numbers following the distribution of this interface using the IRandomNumberProvider interface.
//
// File Format:
// <pre>
// <histogram>
//     <bin low="[lower bound of type cValue]"/>[count: int]</bin>
//     ...
// </histogram>
// </pre>
simple Histogram
{
    parameters:
        xml histogramConfig = default(xml("<histrogram></histogram>"));
        @class(Histogram);
        @display("i=block/delay");
}