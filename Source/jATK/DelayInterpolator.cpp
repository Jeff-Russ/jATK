/*
 ==============================================================================
 
 DelayInterpolator.cpp
 Created: 12 Mar 2015 5:56:23pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#include "DelayInterpolator.h"

namespace jATK
{
    ///=========================================================================
    DelayInterpolator::DelayInterpolator() { this->initialize (1, 1, 0); };
    DelayInterpolator::DelayInterpolator (int bufferSize, int delayInSamples,
                                          int currentIdx )
    {   this->initialize (bufferSize, delayInSamples, currentIdx);
    };
    DelayInterpolator::DelayInterpolator (int bufferSize, audio delayInSamples,
                                          int currentIdx )
    {   this->initialize (bufferSize, delayInSamples, currentIdx);
    };
    DelayInterpolator::~DelayInterpolator(){};
    
    void DelayInterpolator::initialize (int bufferSize, int delayInSamples,
                                        int currentIdx )
    {   bufSize = bufferSize;
        dlyInSampInt = delayInSamples;
        dlyInSampFlt = delayInSamples;
        curIdx = currentIdx;
    };
    void DelayInterpolator::initialize (int bufferSize, audio delayInSamples,
                                        int currentIdx )
    {   bufSize = bufferSize;
        dlyInSampInt = (int)delayInSamples;
        dlyInSampFlt = delayInSamples;
        curIdx = currentIdx;
    };
    void DelayInterpolator::setSize (int bufferSize) { bufSize = bufferSize; };
    void DelayInterpolator::setCurrentIdx (int currentIdx) {curIdx = currentIdx;};
    void DelayInterpolator::setDelayInSamples (int delayInSamples)
    {   dlyInSampInt = delayInSamples;
    };
    void DelayInterpolator::setDelayInSamples (audio delayInSamples)
    {   dlyInSampFlt = delayInSamples;
    };
    void DelayInterpolator::interpolateIndexes()
    {   dlyInSampInt = (int)dlyInSampFlt;
        
        idxMin1Offs = (intClipMin (dlyInSampInt - 1));
        idxPlus0Offs = dlyInSampInt;
        idxPlus1Offs = dlyInSampInt + 1;
        idxPlus2Offs = dlyInSampInt + 2;
        
        idxMin1  = wrapMin (curIdx - idxMin1Offs,  bufSize);
        idxPlus0 = wrapMin (curIdx - idxPlus0Offs, bufSize);
        idxPlus1 = wrapMin (curIdx - idxPlus1Offs, bufSize);
        idxPlus2 = wrapMin (curIdx - idxPlus2Offs, bufSize);
    };
    int DelayInterpolator::getIndexMin1()  { return idxMin1;  };
    int DelayInterpolator::getIndexPlus0() { return idxPlus0; };
    int DelayInterpolator::getIndexPlus1() { return idxPlus1; };
    int DelayInterpolator::getIndexPlus2() { return idxPlus2; };
    
    int DelayInterpolator::getIndex()
    {   return wrapMin ( (curIdx - dlyInSampInt), bufSize);
    };
    audio DelayInterpolator::interpolateAudio (audio minus1, audio plus0,
                                          audio plus1,  audio plus2)
    {   return Interp4_AudioArr ( (dlyInSampFlt - (audio)dlyInSampInt),
                          minus1, plus0, plus1, plus2);
    };
    audio out;
    
    ///=========================================================================
} // end namespace jATK