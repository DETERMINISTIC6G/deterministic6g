///*
// * PKDelayer.h
// *
// *  Created on: Jun 22, 2023
// *      Author: dan
// */
//
//#ifndef PKDELAYER_H_
//#define PKDELAYER_H_
//
//#include "inet/common/INETDefs.h"
//#include "inet/queueing/base/PacketDelayerBase.h"
//
//namespace pkdelay {
//
//using namespace inet;
//using namespace queueing;
//
//class INET_API PKDelayer // public PacketDelayerBase , public DistributionBase
//{
////  protected:
////    cRNG *rng;
////    cPar *delayParameter = nullptr;
////    cPar *bitrateParameter = nullptr;
////    mutable double delayTime = 0; // or declare clocktime_t delayTime
////
//////    cPar *mean = nullptr;
//////    cPar *stddev = nullptr;
//////    cHistogram *delayStats; // Declare cHistogram object
////
////  protected:
////    virtual void initialize(int stage) override;
////
////    /* ---------------------------- Random Delay Time ---------------------------- */
//////    virtual double ArbitraryDelayTime(double mean, double stddev) const override;
////    /* --------------------------------------------------------------------------- */
////
////    virtual clocktime_t computeDelay(Packet *packet) const override;
////
//////    virtual clocktime_t Static(clocktime_t staticDelay) const override;
////
//////// For creating a histogram below -----------------------------------------------
//////    virtual void finish() override; // Add finish method to record the histogram
//////
//////  public:
//////    virtual ~PKDelayer(); // Add destructor declaration
//////// ------------------------------------------------------------------------------
//
//
////  public:
////    static cNEDValue ned_Static(cComponent *context, cNEDValue argv[], int argc);
//
//};
//
//} // PKDelayer
//
//#endif /* PKDELAYER_H_ */
