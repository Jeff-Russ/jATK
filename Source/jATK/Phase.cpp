/*==============================================================================
 Phase.cpp  :   Jeff's (Juce) Audio ToolKit 
 Created: 20 Feb 2015 12:24:49pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#include "Phase.h"

namespace jATK
{
    ///=========================================================================
    PhaseUni::PhaseUni() { sr = 0; fq = 0; ph = 0; }
    PhaseUni::~PhaseUni() {}
    void PhaseUni::setPhase (Audio phase) { ph = phase;}
    float PhaseUni::get() { return ph; }

    PhaseUni::PhaseUni (PreAudio samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0.5;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void PhaseUni::setSR (PreAudio samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void PhaseUni::setFreq (PreAudio frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
    }
    Audio PhaseUni::next()
    {	ph += incr;
        if (ph > 1.0f)
            ph -= 1.0f;
        return ph;
    }
    Audio PhaseUni::next (PreAudio frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
        return ph;
    }
    ///=========================================================================
    
    PhaseBip::PhaseBip() { sr = 0; fq = 0; ph = 0; }
    PhaseBip::~PhaseBip() {}
    void PhaseBip::setPhase (Audio phase) {ph = phase; }
    Audio PhaseBip::get() { return ph; }

    PhaseBip::PhaseBip (double samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0;
        srX = 1 / samplerate;
        incr = srX * fq;
    }
    void PhaseBip::setSR (PreAudio samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = srX * fq;
    }
    void PhaseBip::setFreq (PreAudio frequency)
    {	fq = frequency;
        incr = srX * fq;
    }
    Audio PhaseBip::next()
    {	ph += incr;
        if (ph > 0.5)
            ph -= 1.0;
        return ph;
    }
    Audio PhaseBip::next (PreAudio frequency)
    {	fq = frequency;
        incr = srX * fq;
        return ph;
    }
    ///=========================================================================
} // end namespace jATK