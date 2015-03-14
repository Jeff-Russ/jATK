/*==============================================================================
 Phase.cpp  :   Jeff's (Juce) Audio ToolKit 
 Created: 20 Feb 2015 12:24:49pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#include "Phase.h"

namespace
{   double TWOPI = 6.283185307179586476925286766559;
    double PI = 6.283185307179586476925286766559 * 0.5;
    float TWOPIf = 6.283185307179586476925286766559;
    float PIf = 6.283185307179586476925286766559 * 0.5;
}
namespace jATK
{
    ///=========================================================================
    PhaseUni::PhaseUni() { sr = 0; fq = 0; ph = 0; }
    PhaseUni::~PhaseUni() {}
    void PhaseUni::setPhase (audio phase) { ph = phase;}
    float PhaseUni::get() { return ph; }

    PhaseUni::PhaseUni (preAudio samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0.5;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void PhaseUni::setSR (preAudio samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void PhaseUni::setFreq (preAudio frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
    }
    audio PhaseUni::next()
    {	ph += incr;
        if (ph > 1.0f)
            ph -= 1.0f;
        return ph;
    }
    audio PhaseUni::next (preAudio frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
        return ph;
    }
    ///=========================================================================
    
    PhaseBip::PhaseBip() { sr = 0; fq = 0; ph = 0; }
    PhaseBip::~PhaseBip() {}
    void PhaseBip::setPhase (audio phase) {ph = phase; }
    audio PhaseBip::get() { return ph; }

    PhaseBip::PhaseBip (double samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0;
        srX = 1 / samplerate;
        incr = srX * fq;
    }
    void PhaseBip::setSR (preAudio samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = srX * fq;
    }
    void PhaseBip::setFreq (preAudio frequency)
    {	fq = frequency;
        incr = srX * fq;
    }
    audio PhaseBip::next()
    {	ph += incr;
        if (ph > 0.5)
            ph -= 1.0;
        return ph;
    }
    audio PhaseBip::next (preAudio frequency)
    {	fq = frequency;
        incr = srX * fq;
        return ph;
    }
    ///=========================================================================
} // end namespace jATK