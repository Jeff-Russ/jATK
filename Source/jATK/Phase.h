/*
 ==============================================================================
 
 Phase.h
 Created: 20 Feb 2015 12:24:49pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#ifndef PHASE_H_INCLUDED
#define PHASE_H_INCLUDED
#include <cmath>

//#include "Types.h"

namespace jATK
{
    ///=============================================================================
    
    inline float wrap1 (float phase)
    {   return fmodf(phase, 1.0f);
    }
    inline double wrap1 (double phase)
    {   return fmodf(phase, 1.0);
    }
    ///=============================================================================
    
    inline float ratio1 (float phase, float ratio)
    {   return fmodf((phase * ratio),1.0f);
    }
    inline float ratio1 (float phase, double ratio)
    {   return fmodf((phase * (float)ratio),1.0f);
    }
    inline double ratio1 (double phase, double ratio)
    {   return fmodf((phase * ratio),1.0);
    }
    ///=============================================================================
    
    inline float phaseDistort (float phase, float knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5f;
    else return ( (1 / (1 - knee)) * (phase - knee) * 0.5f ) + 0.5f;
    }
    inline double phaseDistort (double phase, double knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5;
    else return ( (1 / (1 - knee)) * (phase - knee) * 0.5 ) + 0.5;
    }
    ///=============================================================================
    
    class Phase1Float 	// 0...1 phasor
    {
    public:
        Phase1Float();                   // constructor
        Phase1Float (double samplerate); // constructor with float samplerate
        ~Phase1Float();                  // destructor
        
        void setSR   (double samplerate);// set sample rate
        void setFreq (double freqency);  // set freq but don't advance
        void setPhase(float phase);      // set phase but don't advance
        float next   (double frequency); // set freq, advance and get
        float next();				  	 // get next phase position
        float get();                     // get phase without advancement
    private: 			// private variables
        float  ph;		// current state
        double sr; 		// sample rate
        double fq;		// frequency
        double srX;		// srX * fq = incr
        float  incr;    // increment value per sample
    };
    ///=============================================================================
    
    class Phase1Double 	// 0...1 phasor
    {
    public:
        Phase1Double();                   // constructor
        Phase1Double (double samplerate); // constructor with float samplerate
        ~Phase1Double();                  // destructor
        
        void setSR   (double samplerate); // set sample rate
        void setFreq (double freqency);   // set freq but don't advance
        void setPhase(double phase);      // set phase but don't advance
        double next  (double frequency);  // set freq, advance and get
        double next();				  	  // get next phase position
        double get();                     // get phase without advancement
    private: 			// private variables
        double ph;		// current state
        double sr; 		// sample rate
        double fq;		// frequency
        double srX;		// srX * fq = incr
        double incr;    // increment value per sample
    };
    ///=========================================================================
    
    
    class PhaseBipFloat 	// -0.5...0.5 phasor
    {
    public:
        PhaseBipFloat();                   // constructor
        PhaseBipFloat (double samplerate); // constructor with float samplerate
        ~PhaseBipFloat();                  // destructor
        
        void setSR   (double samplerate);// set sample rate
        void setFreq (double freqency);  // set freq but don't advance
        void setPhase(float phase);      // set phase but don't advance
        float next   (double frequency); // set freq, advance and get
        float next();				  	 // get next phase position
        float get();                     // get phase without advancement
    private: 			// private variables
        float  ph;		// current state
        double sr; 		// sample rate
        double fq;		// frequency
        double srX;		// srX * fq = incr
        float  incr;    // increment value per sample
    };
    ///=========================================================================
    
    class PhaseBipDouble 	// -0.5...0.5 phasor
    {
    public:
        PhaseBipDouble();                   // constructor
        PhaseBipDouble (double samplerate); // constructor with float samplerate
        ~PhaseBipDouble();                  // destructor
        
        void setSR   (double samplerate); // set sample rate
        void setFreq (double freqency);   // set freq but don't advance
        void setPhase(double phase);      // set phase but don't advance
        double next  (double frequency);  // set freq, advance and get
        double next();				  	  // get next phase position
        double get();                     // get phase without advancement
    private: 			// private variables
        double ph;		// current state
        double sr; 		// sample rate
        double fq;		// frequency
        double srX;		// srX * fq = incr
        double incr;    // increment value per sample
    };
    ///=========================================================================
    
    class PhasePiFloat	// -3.14...3.14 phasor
    {
    public:
        PhasePiFloat();                   // constructor
        PhasePiFloat(double samplerate); // constructor with float samplerate
        ~PhasePiFloat();                  // destructor
        
        void setSR   (double samplerate); // set sample rate
        void setFreq (double freqency);   // set freq but don't advance
        void setPhase(float phase);       // set phase but don't advance
        float next   (double frequency);  // set freq, advance and get
        float next();				  	  // get next phase position
        float get();                      // get phase without advancement
    private: 			// private variables
        float ph;		// current state
        double sr; 		// sample rate
        double fq;		// frequency
        double srX;		// srX * fq = incr
        float incr;     // increment value per sample
    };
    ///=========================================================================
    
    class PhasePiDouble	// -3.14...3.14 phasor
    {
    public:
        PhasePiDouble();                   // constructor
        PhasePiDouble(double samplerate); // constructor with float samplerate
        ~PhasePiDouble();                  // destructor
        
        void setSR   (double samplerate); // set sample rate
        void setFreq (double freqency);   // set freq but don't advance
        void setPhase(double phase);      // set phase but don't advance
        double next  (double frequency);  // set freq, advance and get
        double next();				  	  // get next phase position
        double get();                     // get phase without advancement
    private: 			// private variables
        double ph;		// current state
        double sr; 		// sample rate
        double fq;		// frequency
        double srX;		// srX * fq = incr
        double incr;    // increment value per sample
    };
    ///=========================================================================
} // end namespace jATK

#endif  // PHASE_H_INCLUDED
