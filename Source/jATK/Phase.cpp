/*==============================================================================
 Phase.cpp  :   Jeff's (Juce) Audio ToolKit 
 Created: 20 Feb 2015 12:24:49pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#include "Phase.h"
//#include "Types.h"

namespace
{   double TWOPI = 6.283185307179586476925286766559;
    double PI = 6.283185307179586476925286766559 * 0.5;
    float TWOPIf = 6.283185307179586476925286766559;
    float PIf = 6.283185307179586476925286766559 * 0.5;
}
namespace jATK
{
    ///=========================================================================
    Phase1::Phase1() { sr = 0; fq = 0; ph = 0; }
    Phase1::~Phase1() {}
    void Phase1::setPhase (float phase) { ph = phase;}
    float Phase1::get() { return ph; }

    Phase1::Phase1 (preAudio samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0.5;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void Phase1::setSR (preAudio samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void Phase1::setFreq (preAudio frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
    }
    audioHQ Phase1::next()
    {	ph += incr;
        if (ph > 1.0f)
            ph -= 1.0f;
        return ph;
    }
    audioHQ Phase1::next (preAudio frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
        return ph;
    }
    ///=========================================================================
    
    PhaseBipFloat::PhaseBipFloat() { sr = 0; fq = 0; ph = 0; }
    PhaseBipFloat::~PhaseBipFloat() {}
    void PhaseBipFloat::setPhase (float phase) { ph = phase; }
    float PhaseBipFloat::get() { return ph; }    
    
    PhaseBipFloat::PhaseBipFloat (double samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0.5;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void PhaseBipFloat::setSR (double samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = (float)(srX * fq);
    }
    void PhaseBipFloat::setFreq (double frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
    }
    float PhaseBipFloat::next()
    {	ph += incr;
        if (ph > 0.5f)
            ph -= 1.0f;
        return ph;
    }
    float PhaseBipFloat::next (double frequency)
    {	fq = frequency;
        incr = (float)(srX * fq);
        return ph;
    }
    ///=========================================================================
    
    PhaseBipDouble::PhaseBipDouble() { sr = 0; fq = 0; ph = 0; }
    PhaseBipDouble::~PhaseBipDouble() {}
    void PhaseBipDouble::setPhase (double phase) {ph = phase; }
    double PhaseBipDouble::get() { return ph; }

    PhaseBipDouble::PhaseBipDouble (double samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0;
        srX = 1 / samplerate;
        incr = srX * fq;
    }
    void PhaseBipDouble::setSR (double samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = srX * fq;
    }
    void PhaseBipDouble::setFreq (double frequency)
    {	fq = frequency;
        incr = srX * fq;
    }
    double PhaseBipDouble::next()
    {	ph += incr;
        if (ph > 0.5)
            ph -= 1.0;
        return ph;
    }
    double PhaseBipDouble::next (double frequency)
    {	fq = frequency;
        incr = srX * fq;
        return ph;
    }
    ///=========================================================================
    
    PhasePiFloat::PhasePiFloat() { sr = 0; fq = 0; ph = 0; }
    PhasePiFloat::~PhasePiFloat() {}
    void PhasePiFloat::setPhase (float phase) {	ph = phase; }
    float PhasePiFloat::get() { return ph; }

    PhasePiFloat::PhasePiFloat (double samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0.0f;
        srX = 1 / samplerate;
        incr = (float)(srX * fq / TWOPI);
    }
    void PhasePiFloat::setSR (double samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = (float)(srX * fq / TWOPI);
    }
    void PhasePiFloat::setFreq (double frequency)
    {	fq = frequency;
        incr = (float)(srX * fq / TWOPI);
    }
    float PhasePiFloat::next()
    {	ph += incr;
        if (ph > PIf)
            ph -= PIf;
        return ph;
    }
    float PhasePiFloat::next (double frequency)
    {	fq = frequency;
        incr = (float)(srX * fq / TWOPI);
        return ph;
    }
    ///=========================================================================
    
    PhasePiDouble::PhasePiDouble() { sr = 0; fq = 0; ph = 0; }
    PhasePiDouble::~PhasePiDouble() {}
    void PhasePiDouble::setPhase (double phase) { ph = phase; }
    double PhasePiDouble::get() { return ph; }
    
    PhasePiDouble::PhasePiDouble (double samplerate)
    {	sr = samplerate;
        fq = 0;
        ph = 0;
        srX = 1 / samplerate;
        incr = srX * fq;
    }
    void PhasePiDouble::setSR (double samplerate)
    {	sr = samplerate;
        srX = 1 / samplerate;
        incr = srX * fq / TWOPI;
    }
    void PhasePiDouble::setFreq (double frequency)
    {	fq = frequency;
        incr = srX * fq / TWOPI;
    }
    double PhasePiDouble::next()
    {	ph += incr;
        if (ph > PI)
            ph -= PI;
        return ph;
    }
    double PhasePiDouble::next (double frequency)
    {	fq = frequency;
        incr = srX * fq / TWOPI;
        return ph;
    }
} // end namespace jATK