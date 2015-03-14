/*==============================================================================
 AudioBuffer.cpp    :   Jeff's (Juce) Audio ToolKit
 Created: 20 Feb 2015 3:59:03pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#include "AudioBuffer.h"
#include "helpers.h"
#include <cmath>

namespace jATK
{
    ///=== AudioBuffer class implementation ====================================
    
    AudioBuffer::AudioBuffer()                { this->setSize(44100);      }
    AudioBuffer::AudioBuffer (int bufferSize) { this->setSize(bufferSize); }
    AudioBuffer::~AudioBuffer()               { this->deleteBuffer();      }
    void AudioBuffer::deleteBuffer()          { delete[] array;            }
    int  AudioBuffer::getSize()               { return bufSize;            }
    void AudioBuffer::setSize (int bufferSize)
    {   bufSize = bufferSize;
        bufN = bufSize - 1;
        array = new audio [bufSize];
        this->clear();
    }
    void AudioBuffer::clear()
    {   for (int i = 0; i < bufSize; i++) array[i] = 0.0;
        writeIdx = 0;
    }
    void AudioBuffer::write (audio sample)
    {   if (writeIdx < bufN) { writeIdx++; }
        else { writeIdx = 0; }
        array [writeIdx] = sample;
    }
    audio AudioBuffer::getDelayedSample (int offSet)
    {   if (offSet <= bufSize && offSet >= 0)
            /*everything was fine*/{ /* do nothing */  }
        else if (offSet > bufSize) { offSet = bufSize; }
        else /* offSet was neg. */ { offSet = -offSet; }
        return array [wrapMin (writeIdx - offSet, bufN)];
    }
    ///=== END AudioBuffer class implementation ================================
    
    ///=== AudioBufferIO class implementation ==================================
    
    AudioBufferIO::AudioBufferIO() { this->initialize (1, 1, 0); };
    AudioBufferIO::AudioBufferIO (int bufferSize, int delayInSamples,
                                  int currentIdx )
    {   this->initialize (bufferSize, delayInSamples, currentIdx);
    };
    AudioBufferIO::AudioBufferIO (int bufferSize, audio delayInSamples,
                                  int currentIdx )
    {   this->initialize (bufferSize, delayInSamples, currentIdx);
    };
    AudioBufferIO::~AudioBufferIO(){};
    
    void AudioBufferIO::initialize (int bufferSize, int delayInSamples,
                                    int currentIdx )
    {   bufSize = bufferSize;
        dlyInSampInt = delayInSamples;
        dlyInSampFlt = delayInSamples;
        curIdx = currentIdx;
    };
    void AudioBufferIO::initialize (int bufferSize, audio delayInSamples,
                                    int currentIdx )
    {   bufSize = bufferSize;
        dlyInSampInt = (int)delayInSamples;
        dlyInSampFlt = delayInSamples;
        curIdx = currentIdx;
    };
    void AudioBufferIO::setSize (int bufferSize) { bufSize = bufferSize; };
    void AudioBufferIO::setCurrentIdx (int currentIdx) {curIdx = currentIdx;};
    void AudioBufferIO::setDelayInSamples (int delayInSamples)
    {   dlyInSampInt = delayInSamples;
    };
    void AudioBufferIO::setDelayInSamples (audio delayInSamples)
    {   dlyInSampFlt = delayInSamples;
    };
    void AudioBufferIO::interpolateIndexes()
    {   dlyInSampInt = (int)dlyInSampFlt;
        
        idxMin1Offs = (clipMin (dlyInSampInt - 1));
        idxPlus0Offs = dlyInSampInt;
        idxPlus1Offs = dlyInSampInt + 1;
        idxPlus2Offs = dlyInSampInt + 2;
        
        idxMin1  = wrapMin (curIdx - idxMin1Offs,  bufSize);
        idxPlus0 = wrapMin (curIdx - idxPlus0Offs, bufSize);
        idxPlus1 = wrapMin (curIdx - idxPlus1Offs, bufSize);
        idxPlus2 = wrapMin (curIdx - idxPlus2Offs, bufSize);
    };
    int AudioBufferIO::getIndexMin1()  { return idxMin1;  };
    int AudioBufferIO::getIndexPlus0() { return idxPlus0; };
    int AudioBufferIO::getIndexPlus1() { return idxPlus1; };
    int AudioBufferIO::getIndexPlus2() { return idxPlus2; };
    
    int AudioBufferIO::getIndex()
    {   return wrapMin ( (curIdx - dlyInSampInt), bufSize);
    };
    audio AudioBufferIO::interpolateAudio (audio minus1, audio plus0,
                                           audio plus1,  audio plus2)
    {   return Interp4_AudioArr ( (dlyInSampFlt - (audio)dlyInSampInt),
                                 minus1, plus0, plus1, plus2);
    };
    audio out;
    
    
} // END namespace jATK