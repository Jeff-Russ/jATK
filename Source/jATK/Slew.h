/*==============================================================================
 Slew.h  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Apr 2015 9:10:28pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef SLEW_H_INCLUDED
#define SLEW_H_INCLUDED

#include <cmath>
#include "helpers.h"

namespace jATK
{
    class Slew
    { public:
        Slew (Audio init, Audio adder = 0.001, Audio subt = 0.001)
            : add(adder),sub(subt), internal(init), prevIn(init), output(init){}
        void reset (Audio init) { output = prevIn = internal = init; }
        void set (Audio adder, Audio subt) {add = adder; sub = subt; }
        
        Audio operator()(Audio input)
        {   if (input != output)
            {
                // determine direction:
                if (input != prevIn) // a new input value is the only time we
                {   diff = input - internal;  // want to find difference and
                    if (diff > 0) { goUp = true; }  // determine direction.
                } // else we will use the current direction
                
                if (goUp)   // process rising output
                {   if (internal < input) { output = internal = internal + add; }
                    else { output = internal = input; } // went too far. set to goal.
                }else       // process falling output
                {   if (internal > input) { output = internal = internal - sub; }
                    else { output = internal = input; } // went too far. set to goal.
                }
            } // else we will use the previous output
            return output;
        }
      protected: Audio add, sub;
      private:   Audio diff, internal, prevIn, output;  bool goUp;
    };

    class SlewLimiter : public Slew
    { public:
        SlewLimiter (Audio sRate, Audio initValue) : Slew(initValue) { msPerSample = 1000 / sRate; }
        void setSRate (Audio sRate) { msPerSample = 1000 / sRate; }
        void set (Audio upMsPer1, Audio dnMsPer1)
        {   up = upMsPer1; dn = dnMsPer1; this->calc(); }
      private:
        void calc() { Slew::add = msPerSample / up; Slew::sub = msPerSample / dn; }
        Audio msPerSample, up, dn;
    };

    class PeakDetector : public SlewLimiter
    { public:
        PeakDetector (Audio sRate) : SlewLimiter(sRate, 0.0) { SlewLimiter::set (0.6f, 50); }
        Audio operator()(Audio input) { return SlewLimiter::operator()( fabs(input) ); }
    };

} // end namespace jATK

#endif  // SLEW_H_INCLUDED

