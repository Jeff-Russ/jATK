/*
 ==============================================================================
 
 Delay.h
 Created: 20 Feb 2015 3:59:03pm
 Author:  jefrus
 
 ==============================================================================
 */

#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

namespace jATK
{
    ///=========================================================================
    
    class DelayBufferFloat  // circular delay buffer
    {
    public:
        DelayBufferFloat (int maxBufSize);
        ~DelayBufferFloat();
        int  getMax();
        void setMax (int maxBufSize);
        void clear();
        void  write (int index);
        void  write (float sample);
        void  write (float sample, int index);
        float read();
        float read  (int index);
    private:
        void deleteBuffer();
        float* array;
        int reserveSize, usedSize, readIdx, writeIdx;
    };
    ///=========================================================================
    
    class DelayBufferDouble  // circular delay buffer
    {
    public:
        DelayBufferDouble (int maxBufSize);
        ~DelayBufferDouble();
        int  getMax();
        void setMax (int maxBufSize);
        void clear();
        void  write (int index);
        void  write (double sample);
        void  write (double sample, int index);
        double read();
        double read  (int index);
    private:
        void deleteBuffer();
        double* array;
        int reserveSize, readIdx, writeIdx;
    };
    ///=========================================================================
    
} // end namespace jATK

#endif  // DELAY_H_INCLUDED
