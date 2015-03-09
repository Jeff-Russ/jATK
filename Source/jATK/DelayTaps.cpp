/*
 ==============================================================================
 
 DelayTaps.cpp
 Created: 8 Mar 2015 2:13:22pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#include "DelayTaps.h"
#include "AudioBuffer.h"

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
        delayBuffer.setMax(MaxBufSize);
        delayBuffer.write(0);
        currentIdx = 0;
    };
    DelayTaps::~DelayTaps(){
    };
    void DelayTaps::toggleInterp (bool interpolation, int tap)
    {   interp[tap] = interpolation;
    };
    void DelayTaps::record(audio audioIn)
    {   delayBuffer.write(audioIn);
        currentIdx = wrapIndex(currentIdx, bufSize);
        delayBuffer.index(currentIdx);
    };
    void DelayTaps::setDelayTapInMs (audio millisec, int tap)
    {   
    };
    void DelayTaps::setDelayLineByIdx (audio indexOffset, int tap)
    {   iOffsets[tap] = indexOffset;
    };
    audio DelayTaps::getDelayedSample (int tap)
    {
    };
    void DelayTaps::resize (int bufferSize)
    {   bufSize = bufferSize;
        delayBuffer.clear();
        currentIdx = 0;
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
    

    float srate;
    int numOfTaps;
    vector<bool> interp;
    vector<audio> iOffsets;
    
    ///=========================================================================
} // end namespace jATK