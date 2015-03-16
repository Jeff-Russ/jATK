/*==============================================================================
 DelayTaps.h    :   Jeff's (Juce) Audio ToolKit
 Created: 8 Mar 2015 2:13:22pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef DELAYTAPS_H_INCLUDED
#define DELAYTAPS_H_INCLUDED

#include "helpers.h"
#include "CAArray.h"

#include <vector>
using namespace std;

namespace jATK
{
    ///=========================================================================
    class DelayTaps
    {
    public:
        DelayTaps (int maxBufferSize,
                   int bufferSize,
                   float samplerate,
                   int numberOfTaps = 1,
                   bool interpolation = false);
        ~DelayTaps();
        
        void toggleInterp      (bool interpolation, int tap = 1);
        void record            (Audio AudioIn);
        void setDelayTapInMs   (Audio millisec,    int tap = 1);
        void setDelayLineByIdx (Audio indexOffset, int tap = 1);
        
        void resize (int bufferSize);                   // resize+clear all buffers
        void setNumOfTaps (int numberOfTaps);           // create+clear or delete taps
        void clear();                                   // zero out the buffer
        void initialize(int bufferSize, int numberOfTaps); // all in one
        
        Audio getDelayedSample (int tap = 1);
        
    private:
        int MaxBufSize;
        int bufSize;
        CAArray delayBuffer;
        //DelayInterpolator bufferShell;
        float srate;
        int numOfTaps;
        int currentIdx;
        vector<bool> interp;
        vector<Audio> iOffsets;
    };
    
    ///=========================================================================
} // end namespace jATK

#endif  // DELAYTAPS_H_INCLUDED
