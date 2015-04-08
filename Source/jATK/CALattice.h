/*==============================================================================
 CALattice.h  :   Jeff's (Juce) Audio ToolKit
 Created: 16 Mar 2015 2:41:27pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 ===============================================================================
 Array based classes:
                          OscLUT---SineLUT---AdditiveSineLUT
 CAArray--|--LookupTable_/
          |              l_SamplerLUT
          |
          |--Delay---MultiTapDelay
          |
          \-Interpolate   APFilter
           \             /
            CALattice---|-DiffDelay
                         \
                          CombFilter
 =============================================================================*/

#ifndef CALATTICE_H_INCLUDED
#define CALATTICE_H_INCLUDED

#include "CAArray.h"

namespace jATK
{
    class CALattice : public CAArray
    {
    public:
        CALattice();
        CALattice (int bufferSize, PreAudio sampleRate, PreAudio delayInMs,
                   Audio factor,      // factor is FFwrdAmt, -factor is FBackAmt
                   int interpolation);// 0 2 or 4 point interpolation.
        
        CALattice (int bufferSize, PreAudio sampleRate, PreAudio delayInMs,
                   PreAudio FeedForwardAmt, PreAudio FeedBackAmt, int interp);
        
        void resetBuffer(); // clears buffer, as does the next method:
        void resetBuffer  (int bufferSize, PreAudio sampleRate, int interp);
        void setDelayInMs (PreAudio delayInMS);
        void setFactor    (PreAudio factor);    // FFAmt=factor; FBAmt= -factor;
        void setFForwAmt  (PreAudio FeedForwardAmt);
        void setFBackAmt  (PreAudio FeedForwardAmt);
        
        int   getBuffSize();    // get the maximum delay available, in samples
        Audio getDelayInMs();   // get the current delay in milliseconds
        Audio getFactor();      // get the FFAmt, which is -FBAmt
        Audio getFForwAmt();    // feedforward amount 
        Audio getFBackAmt();    // feedback amount
        
        Audio processLE  (Audio audioIn); // Late FFwrd, Early FBack
        Audio processLE  (Audio audioIn, Audio delayInMs, Audio factor);
        Audio processEL  (Audio audioIn); // Early FFwrd, Late FBack
        Audio processEL  (Audio audioIn, Audio delayInMs, Audio factor);
        Audio processLL  (Audio audioIn); // Late FFwrd, Late FBack
        Audio processLL  (Audio audioIn, Audio delayInMs, Audio factor);
        Audio processEE  (Audio audioIn); // Early FFwrd, Early FBack
        Audio processEE  (Audio audioIn, Audio delayInMs, Audio factor);
        Audio getOutput();
        
    private:
    };
} // end namespace jATK
#endif  // CALATTICE_H_INCLUDED
