/*
 ==============================================================================
 
 Sine.h
 Created: 20 Feb 2015 12:25:15pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#ifndef SINE_H_INCLUDED
#define SINE_H_INCLUDED
#include <cmath>

namespace jATK
{
    ///=========================================================================
    
    inline float sine4 (float phase)
    {   float absPh = fabs(phase);
        return (phase * 68.5949f) * (absPh + 0.232963f) *
        (absPh - 0.5f)  * (absPh - 0.732963f);
    }
    inline double sine4 (double phase)
    {   double absPh = fabs(phase);
        return (phase * 68.5949) * (absPh + 0.232963) *
        (absPh - 0.5)  * (absPh - 0.732963);
    }
    ///=========================================================================
    
    inline float sine8 (float phase)
    {   float absPh = fabs(phase);
        return phase *  60.2522 * ((absPh * (absPh + 1.05802f)) + 0.436501f) *
        (absPh + 0.424933f) * ((absPh * (absPh - 2.05802f)) + 1.21551f) *
        (absPh - 0.5f) * (absPh - 0.924933f);
    }
    inline double sine8 (double phase)
    {   double absPh = fabs(phase);
        return phase *  60.2522 * ((absPh * (absPh + 1.05802)) + 0.436501) *
        (absPh + 0.424933) * ((absPh * (absPh - 2.05802)) + 1.21551) *
        (absPh - 0.5) * (absPh - 0.924933);
    }
    
} // end namespace jATK


#endif  // SINE_H_INCLUDED
