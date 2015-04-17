/*==============================================================================
 MidiRate.h  :   Jeff's (Juce) Audio ToolKit
 Created: 16 Apr 2015 10:41:44pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef MIDIRATE_H_INCLUDED
#define MIDIRATE_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    class MidiRate
    { public:
        MidiRate (Audio sRate, int bufferSize ) : sr(sRate), bSize(bufferSize)
        { this->calc(); }
        
        void setSRate (Audio sRate) { sr = sRate; this->calc(); }
        void setBufferSize (int bufferSize) { bSize = bufferSize; this->calc();}
        void setMidiRate (int midiRate) { mRate = midiRate; this->calc(); }
        int operator()() { return mBufSize; }
        
      private:
        void calc() { mBufSize = mRate / sr * bSize; }
        Audio sr; int bSize, mRate, mBufSize;
 
    };

} // end namespace jATK
#endif  // MIDIRATE_H_INCLUDED
