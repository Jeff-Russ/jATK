/*==============================================================================
 Phase.h    :   Jeff's (Juce) Audio ToolKit
 Created: 20 Feb 2015 12:24:49pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#ifndef PHASE_H_INCLUDED
#define PHASE_H_INCLUDED

#include <cmath>
#include "helpers.h"

namespace jATK
{
    class PhaseUni 	// 0...1 phasor
    {
    public:
        PhaseUni();                     // constructor
        PhaseUni (preAudio samplerate); // constructor with float samplerate
        ~PhaseUni();                    // destructor
        
        void setSR   (preAudio samplerate);// set sample rate
        void setFreq (preAudio freqency);  // set freq but don't advance
        void setPhase(audio phase);        // set phase but don't advance
        audio next   (preAudio frequency); // set freq, advance and get
        audio next();				  	   // get next phase position
        audio get();                       // get phase without advancement
    private: 			// private variables
        audio ph;		// current state
        audio sr; 		// sample rate
        audio fq;		// frequency
        audio srX;		// srX * fq = incr
        audio incr;     // increment value per sample
    };
    ///=========================================================================
    class PhaseBip 	// -0.5...0.5 phasor
    {
    public:
        PhaseBip();                     // constructor
        PhaseBip (preAudio samplerate); // constructor with float samplerate
        ~PhaseBip();                    // destructor
        
        void setSR   (preAudio samplerate); // set sample rate
        void setFreq (preAudio freqency);   // set freq but don't advance
        void setPhase(audio phase);         // set phase but don't advance
        audio next   (preAudio frequency);  // set freq, advance and get
        audio next();				  	    // get next phase position
        audio get();                        // get phase without advancement
    private: 			// private variables
        audio ph;		// current state
        audio sr; 		// sample rate
        audio fq;		// frequency
        audio srX;		// srX * fq = incr
        audio incr;     // increment value per sample
    };
    ///=========================================================================
} // end namespace jATK

#endif  // PHASE_H_INCLUDED
