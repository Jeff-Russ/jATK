/*==============================================================================
 AudioBuffer.h  :   Jeff's (Juce) Audio ToolKit
 Created: 20 Feb 2015 3:59:03pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#ifndef AUDIOBUFFFER_H_INCLUDED
#define AUDIOBUFFER_H_INCLUDED

#include "helpers.h"

namespace jATK
{   ///=========================================================================
    class AudioBuffer
    {  public:
        AudioBuffer();
        AudioBuffer (int bufferSize);
        ~AudioBuffer();
        int  getSize();
        void setSize (int bufferSize);
        void clear();
        void  write (audio sample);
        audio getDelayedSample  (int offSet);
      private:
        void deleteBuffer();
        audio* array;
        int bufSize, bufN, writeIdx, readIdx;
    };
    ///=========================================================================
    class AudioBufferIO
    { public:
        AudioBufferIO();
        AudioBufferIO (int bufferSize, int delayInSamples, int currentIdx=0);
        AudioBufferIO (int bufferSize, audio delayInSamples, int currentIdx=0);
        ~AudioBufferIO();
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

#endif  // AUDIOBUFFFER_H_INCLUDED
