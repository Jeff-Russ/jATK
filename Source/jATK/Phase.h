/*==============================================================================
 Phase.h    :   Jeff's (Juce) Audio ToolKit
 Created: 20 Feb 2015 12:24:49pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

/// this file is nearly complete but needs testing ============================

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
        PhaseUni (PreAudio samplerate); // constructor with float samplerate
        ~PhaseUni();                    // destructor
        
        void setSR   (PreAudio samplerate);// set sample rate
        void setFreq (PreAudio freqency);  // set freq but don't advance
        void setPhase(Audio phase);        // set phase but don't advance
        Audio next   (PreAudio frequency); // set freq, advance and get
        Audio next();				  	   // get next phase position
        Audio get();                       // get phase without advancement
    private: 			// private variables
        Audio ph;		// current state
        Audio sr; 		// sample rate
        Audio fq;		// frequency
        Audio srX;		// srX * fq = incr
        Audio incr;     // increment value per sample
    };
    ///=========================================================================
    class PhaseBip 	// -0.5...0.5 phasor
    {
    public:
        PhaseBip();                     // constructor
        PhaseBip (PreAudio samplerate); // constructor with float samplerate
        ~PhaseBip();                    // destructor
        
        void setSR   (PreAudio samplerate); // set sample rate
        void setFreq (PreAudio freqency);   // set freq but don't advance
        void setPhase(Audio phase);         // set phase but don't advance
        Audio next   (PreAudio frequency);  // set freq, advance and get
        Audio next();				  	    // get next phase position
        Audio get();                        // get phase without advancement
    private: 			// private variables
        Audio ph;		// current state
        Audio sr; 		// sample rate
        Audio fq;		// frequency
        Audio srX;		// srX * fq = incr
        Audio incr;     // increment value per sample
    };
    ///=========================================================================
} // end namespace jATK

#endif  // PHASE_H_INCLUDED
