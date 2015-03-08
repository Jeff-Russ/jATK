/*
 ==============================================================================
 
 Delay.cpp
 Created: 20 Feb 2015 3:59:03pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#include "DelayBuffer.h"
#include "types.h"

namespace jATK
{
    ///=========================================================================
    
    DelayBuffer::DelayBuffer(int size) { this->setMax(size);  }
    DelayBuffer::~DelayBuffer()        { this->deleteBuffer();}
    void DelayBuffer::deleteBuffer()        { delete[] array;      }
    int  DelayBuffer::getMax()              { return reserveSize;  }
    void DelayBuffer::setMax (int maxBufSize)
    {   reserveSize = maxBufSize;
        usedSize = maxBufSize;
        array = new audio [maxBufSize];
        this->clear();
    }
    void DelayBuffer::clear()
    {   for (int i = 0; i < reserveSize; i++) array[i] = 0.0f;
    }
    void DelayBuffer::write (int index)    { writeIdx = index;            }
    void DelayBuffer::write (audio sample) {this->write(sample, writeIdx);}
    
    void DelayBuffer::write (audio sample, int index)
    {   writeIdx = index;
        array[writeIdx] = sample;
    }
    audio DelayBuffer::read()
    {   return array[readIdx];
    }
    audio DelayBuffer::read (int index)
    {   readIdx = index;
        return array[readIdx];
    }
    ///=========================================================================
    
} // end namespace jATK