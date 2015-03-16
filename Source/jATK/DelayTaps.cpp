/*==============================================================================
 DelayTaps.cpp  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Mar 2015 2:13:22pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#include "DelayTaps.h"

namespace jATK
{
    ///=========================================================================
    DelayTaps::DelayTaps (int maxBufferSize, int bufferSize, float samplerate,
                          int numberOfTaps, bool interpolation)
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
    void DelayTaps::record (Audio AudioIn)
    {   delayBuffer.write(AudioIn);
        currentIdx = wrapMax(currentIdx, bufSize);
        delayBuffer.index(currentIdx);
    };
    void DelayTaps::setDelayTapInMs (Audio millisec, int tap)
    {   iOffsets[tap] = millisec * 1000 * srate;
        this->setDelayLineByIdx(iOffsets[tap], tap);
    };
    void DelayTaps::setDelayLineByIdx (Audio indexOffset, int tap)
    {   iOffsets[tap] = indexOffset;
    };
    void DelayTaps::resize (int bufferSize)
    {   if (bufferSize != bufSize)
        {   bufSize = bufferSize;
            delayBuffer.clear();
            currentIdx = 0;
        }
    };
    void DelayTaps::setNumOfTaps (int numberOfTaps)
    {   if (numberOfTaps > numOfTaps)
        {   numOfTaps = numberOfTaps;
            interp.resize( numOfTaps, interp[numOfTaps - 1]);
        }else if (numberOfTaps < numOfTaps)
        {   numOfTaps = numberOfTaps;
            interp.resize(numOfTaps);
        }
    };
    void DelayTaps::clear()
    {   delayBuffer.clear();
        currentIdx = 0;
    };
    void DelayTaps::initialize (int bufferSize, int numberOfTaps)
    {   this->setNumOfTaps(numberOfTaps);
        this->resize(bufferSize);
    };
    Audio DelayTaps::getDelayedSample (int tap)
    {   if (!interp[tap])
        {   
            return delayBuffer.read ( (int)iOffsets[tap] ); // change this
        
        }
        else
        {
            
        }
    };
    ///=========================================================================
} // end namespace jATK