/*
 ==============================================================================
 
 Delay.h
 Created: 20 Feb 2015 3:59:03pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#include "types.h"

namespace jATK
{
    ///=========================================================================
    
    class DelayBuffer  // circular delay buffer
    {
    public:
        DelayBuffer (int maxBufSize);
        ~DelayBuffer();
        int  getMax();
        void setMax (int maxBufSize);
        void clear();
        void  write (int index);
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

#endif  // DELAY_H_INCLUDED
