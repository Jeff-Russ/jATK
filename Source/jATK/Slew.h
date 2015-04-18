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
        {   this->input = input;
            if (input != output)
            {   // determine direction only upon new input value:
                if (input != prevIn) { this->calc(input); }
                this->process(input); // process input
            } // else we will use the previous output
            return output;
        }
        bool notArrived() { return input != output; }
        
      protected:
        void calc (Audio input)
        {   diff = input - internal;  // want to find difference and
            if (diff > 0) { goUp = true; }  // determine direction.
        }
        void process(Audio input)
        {   if (goUp)   // process rising output
            {   if (internal < input) { output = internal = internal + add; }
                else { output = internal = input; } // went too far. set to goal.
            }else       // process falling output
            {   if (internal > input) { output = internal = internal - sub; }
                else { output = internal = input; } // went too far. set to goal.
            }
        }
        Audio add, sub, diff, internal; bool goUp;
      protected:
        Audio prevIn, output, input;
    };
    
    class SlewLimiter : public Slew
    { public:
        SlewLimiter (Audio sRate, Audio initValue = 0.f) : Slew(initValue)
        { msPerSample = 1000 / sRate; }
        void setSRate (Audio sRate) { msPerSample = 1000 / sRate; }
        void set (Audio upMsPer1, Audio dnMsPer1)
        {   this->addsub (upMsPer1, dnMsPer1); }
      protected:
        void addsub(Audio upMsPer1, Audio dnMsPer1)
        { Slew::add = msPerSample / upMsPer1; Slew::sub = msPerSample / dnMsPer1;}
        Audio msPerSample;
    };
    
    class LinearRamp : public SlewLimiter
    { public:
        LinearRamp (Audio sRate, Audio initValue) : SlewLimiter (sRate, initValue)
        {}
        void set (Audio upMs, Audio dnMs) { this->upMs = upMs; this->dnMs = dnMs; }
        void calc (Audio input)
        {   diff = input - internal;
            if (diff > 0) { goUp = true; }
            Slew::add =       diff  * SlewLimiter::msPerSample / upMs;
            Slew::sub = fabsf(diff) * SlewLimiter::msPerSample / dnMs;
        }
      private:
        Audio upMs, dnMs;
    };
    
    class PeakDetector : public SlewLimiter
    { public:
        PeakDetector (Audio sRate) : SlewLimiter(sRate, 0.0) { SlewLimiter::set (0.6f, 50); }
        Audio operator()(Audio input) { return SlewLimiter::operator()( fabs(input) ); }
    };
    
    
    //    class NonlinearRamp : public Slew
    //    { public:
    //        NonlinearRamp (Audio sRate, Audio initValue) : Slew(initValue)
    //        { msPerSample = 1000 / sRate; }
    //        void setSRate (Audio sRate) { msPerSample = 1000 / sRate; }
    //        void set (Audio upMs, Audio dnMs)
    //        {   upCoef = msPerSample * upMs; dnCoef = msPerSample * dnMs;  }
    //        Audio operator()(Audio input)
    //        {   if (input != Slew::output)
    //            {   // determine direction only upon new input value:
    //                if (input != Slew::prevIn)
    //                { Slew::calc(input); }
    //                Slew::process(input); // process input
    //                } // else we will use the previous output
    //                return Slew::output;
    //        }
    //      private:
    //        
    //        Audio msPerSample, upCoef, dnCoef;
    //    };
    
} // end namespace jATK

#endif  // SLEW_H_INCLUDED

