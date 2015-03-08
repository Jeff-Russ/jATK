/*
 ==============================================================================
 
 DelayTaps.cpp
 Created: 8 Mar 2015 2:13:22pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#include "DelayTaps.h"
#include "CircularBuffer.h"

namespace jATK
{
    ///=========================================================================
    DelayTaps::DelayTaps (int maxBufferSize,
                          int bufferSize,
                          float samplerate,
                          int numberOfTaps,
                          bool interpolation)
    {   MaxBufSize = maxBufferSize;
        bufSize = bufferSize;
        srate = samplerate;
        numOfTaps = numberOfTaps;
        interp.resize (numberOfTaps, interpolation);
        delayBuffer.setMax(bufSize);
        currentIdx = 0;
    };
    DelayTaps::~DelayTaps(){
    };
    void DelayTaps::toggleInterp (bool interpolation, int tap)
    {
        interp[tap] = interpolation;
    };
    void DelayTaps::record (audio audioIn)
    {
    };
    audio DelayTaps::getDelayTapInMs (audio millisec, int tap)
    {
    };
    audio DelayTaps::getDelayLineByIdx (audio index, int tap)
    {   
    };
    audio DelayTaps::getDelayTap (int tap)
    {
    };
    void DelayTaps::resize (int bufferSize)
    {
    };
    void DelayTaps::setNumOfTaps (int numOfTaps)
    {
    };
    void DelayTaps::clear()
    {
    };
    void DelayTaps::initialize (int bufferSize, int numOfTaps)
    {
    };
    
    int MaxBufSize;
    int bufSize;
    float srate;
    int numOfTaps;
    int currentIdx;
    vector<bool> interp;
    vector<audio> iOffsets;
    
    ///=========================================================================
} // end namespace jATK