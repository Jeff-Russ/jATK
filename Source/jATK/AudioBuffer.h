/*
 ==============================================================================
 
 AudioBuffer.h
 Created: 20 Feb 2015 3:59:03pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#ifndef AUDIOBUFFFER_H_INCLUDED
#define AUDIOBUFFER_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    ///=========================================================================
    
    class AudioBuffer
    {
    public:
        AudioBuffer();
        AudioBuffer (int maxBufSize);
        ~AudioBuffer();
        int  getMax();
        void setMax (int maxBufSize);
        void clear();
        void  index (int index);
        void  write (audio sample);
        void  write (audio sample, int index);
        audio read();
        audio read  (int index);
    private:
        void deleteBuffer();
        audio* array;
        int reserveSize, usedSize, readIdx, writeIdx;
    };
    ///=========================================================================
    
} // end namespace jATK

#endif  // AUDIOBUFFFER_H_INCLUDED
