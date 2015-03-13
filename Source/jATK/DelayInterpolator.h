/*
  ==============================================================================

    DelayInterpolator.h
    Created: 12 Mar 2015 5:56:23pm
    Author:  Jeff-Russ

  ==============================================================================
*/

#ifndef DELAYINTERPOLATOR_H_INCLUDED
#define DELAYINTERPOLATOR_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    ///=========================================================================
    class DelayInterpolator
    {
      public:
        DelayInterpolator();
        DelayInterpolator (int bufferSize, int delayInSamples, int currentIdx=0);
        DelayInterpolator (int bufferSize, audio delayInSamples, int currentIdx=0);
        ~DelayInterpolator();
        
        void initialize (int bufferSize, int delayInSamples, int currentIdx=0);
        void initialize (int bufferSize, audio delayInSamples, int currentIdx=0);
        
        void setSize (int bufferSize);
        void setCurrentIdx (int currentIdx);
        void setDelayInSamples (int delayInSamples);
        void setDelayInSamples (audio delayInSamples);
        void interpolateIndexes ();
        
        int getIndexMin1();
        int getIndexPlus0();
        int getIndexPlus1();
        int getIndexPlus2();
        
        int getIndex();
        
        audio interpolateAudio (audio minus1, audio plus0, audio plus1, audio plus2);
      
      private:
        int bufSize, curIdx, dlyInSampInt, idxMin1Offs, idxPlus0Offs,idxPlus1Offs,
            idxPlus2Offs, idxMin1, idxPlus0, idxPlus1, idxPlus2, dlyIdx;
        
        audio dlyInSampFlt, inMin1, inPlus0, inPlus1, inPlus2, output;
    };
    ///=========================================================================
} // end namespace jATK
#endif  // DELAYINTERPOLATOR_H_INCLUDED
