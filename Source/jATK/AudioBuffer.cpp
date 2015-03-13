/*==============================================================================
 AudioBuffer.cpp    :   Jeff's (Juce) Audio ToolKit
 Created: 20 Feb 2015 3:59:03pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#include "AudioBuffer.h"

namespace jATK
{
    ///=========================================================================
    
    AudioBuffer::AudioBuffer()         { this->setMax(44100); }
    AudioBuffer::AudioBuffer(int size) { this->setMax(size);  }
    AudioBuffer::~AudioBuffer()        { this->deleteBuffer();}
    void AudioBuffer::deleteBuffer()   { delete[] array;      }
    int  AudioBuffer::getMax()         { return reserveSize;  }
    void AudioBuffer::setMax (int maxBufSize)
    {   reserveSize = maxBufSize;
        usedSize = maxBufSize;
        array = new audio [maxBufSize];
        this->clear();
    }
    void AudioBuffer::clear()
    {   for (int i = 0; i < reserveSize; i++) array[i] = 0.0f;
    }
    void AudioBuffer::index (int index)    { writeIdx = index;            }
    void AudioBuffer::write (audio sample) {this->write(sample, writeIdx);}
    
    void AudioBuffer::write (audio sample, int index)
    {   writeIdx = index;
        array[writeIdx] = sample;
    }
    audio AudioBuffer::read()
    {   return array[readIdx];
    }
    audio AudioBuffer::read (int index)
    {   readIdx = index;
        return array[readIdx];
    }
    ///=========================================================================
    
} // end namespace jATK