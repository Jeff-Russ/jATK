/*
 ==============================================================================
 
 DelayTaps.h
 Created: 8 Mar 2015 2:13:22pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#ifndef DELAYTAPS_H_INCLUDED
#define DELAYTAPS_H_INCLUDED

#include "types.h"

namespace jATK
{
///=========================================================================
    
class DelayTaps_Interp
{
public:
    DelayTaps_Interp (int bufSize, int numOfTaps);
    ~DelayTaps_Interp();
    
    audio record           (audio audioIn);
    audio getDelayTapInMs  (audio millisec, int tap = 1);
    audio getDelayLineByIdx(audio index,    int tap = 1);
    
    void resize (int bufSize);                   // resize and clear all buffers
    void setNumOfTaps (int numOfTaps);           // create+clear or delete taps
    void clear();                                // zero out the buffer
    void initialize(int bufSize, int numOfTaps); // all three preceding in one

    
    };
    
    ///=========================================================================
} // end namespace jATK

#endif  // DELAYTAPS_H_INCLUDED
