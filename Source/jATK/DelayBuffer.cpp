/*
 ==============================================================================
 
 Delay.cpp
 Created: 20 Feb 2015 3:59:03pm
 Author:  jefrus
 
 ==============================================================================
 */

#include "DelayBuffer.h"

namespace jATK
{
    ///=========================================================================
    
    DelayBufferFloat::DelayBufferFloat(int size) { this->setMax(size);  }
    DelayBufferFloat::~DelayBufferFloat()        { this->deleteBuffer();}
    void DelayBufferFloat::deleteBuffer()        { delete[] array;      }
    int  DelayBufferFloat::getMax()              { return reserveSize;  }
    void DelayBufferFloat::setMax (int maxBufSize)
    {   reserveSize = maxBufSize;
        usedSize = maxBufSize;
        array = new float [maxBufSize];
        this->clear();
    }
    void DelayBufferFloat::clear()
    {   for (int i = 0; i < reserveSize; i++) array[i] = 0.0f;
    }
    void DelayBufferFloat::write (int index)    { writeIdx = index;            }
    void DelayBufferFloat::write (float sample) {this->write(sample, writeIdx);}
    
    void DelayBufferFloat::write (float sample, int index)
    {   writeIdx = index;
        array[writeIdx] = sample;
    }
    float DelayBufferFloat::read()
    {   return array[readIdx];
    }
    float DelayBufferFloat::read (int index)
    {   readIdx = index;
        return array[readIdx];
    }
    ///=========================================================================
    
    DelayBufferDouble::DelayBufferDouble(int size) { this->setMax(size);  }
    DelayBufferDouble::~DelayBufferDouble()        { this->deleteBuffer();}
    void DelayBufferDouble::deleteBuffer()         { delete[] array;      }
    int  DelayBufferDouble::getMax()               { return reserveSize;  }
    void DelayBufferDouble::setMax (int maxBufSize)
    {   reserveSize = maxBufSize;
        array = new double [maxBufSize];
        this->clear();
    }
    void DelayBufferDouble::clear()
    {   for (int i = 0; i < reserveSize; i++) array[i] = 0.0f;
    }
    void DelayBufferDouble::write (int index)   { writeIdx = index;            }
    void DelayBufferDouble::write(double sample){this->write(sample, writeIdx);}
    
    void DelayBufferDouble::write (double sample, int index)
    {   writeIdx = index;
        array[writeIdx] = sample;
    }
    double DelayBufferDouble::read()
    {   return array[readIdx];
    }
    double DelayBufferDouble::read (int index)
    {   readIdx = index;
        return array[readIdx];
    }
    ///=========================================================================
    
} // end namespace jATK