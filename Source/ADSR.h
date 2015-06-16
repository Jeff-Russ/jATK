//  ADSR.h
//  Created by Nigel Redmon on 12/18/12.
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the ADSR envelope generator and code,
//  read the series of articles by the author, starting here: http://www.earlevel.com/main/2013/06/01/envelope-generators/
//
//  License:
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code for your own purposes, free or commercial.

/* EAMPLE USE:

    // create ADSR env
ADSR *env = new ADSR();

// initialize settings
env->setAttackRate(.1 * sampleRate);  // .1 second
env->setDecayRate(.3 * sampleRate);
env->setReleaseRate(5 * sampleRate);
env->setSustainLevel(.8);
…
// at some point, by MIDI perhaps, the envelope is gated "on"
env->gate(true);
…
// and some time later, it's gated "off"
env->gate(false);
*/

#ifndef ADRS_h
#define ADRS_h

class ADSR {
public:
	ADSR(void);
	~ADSR(void);
	
/*	Call the process function at the control rate (which might be once per sample period, 
    or a lower rate if you’ve implemented a lower control sampling rate); it returns the current envelope output. 
    The getOutput function returns the current output only, for convenience: */
	float process(void);
    float getOutput(void);
    
/*  It may be useful to know what state an envelope generator is in, for sophisticated control applications 
    (typically, though, you won’t need this); a state enum is defined for convenience (for example, ADSR::env_sustain 
    is equivalent to the value 3, and indicates that the current state is Sustain): */
    int getState(void);
    
    // Set the gate state on (true) or off (false):
	void gate(int on);
	
/*	Set the Attack, Decay, and Release rates (in samples—you can multiply time in seconds by the sample rate), 
    and the sustain level (0.0-1.0); calls these when settings change, not at the sample rate: */
    void setAttackRate(float rate);
    void setDecayRate(float rate);
    void setReleaseRate(float rate);
	void setSustainLevel(float level);
	
/*  Adjust the curves of the Attack, or Decay and Release segments, 
    from the initial default values (small number such as 0.0001 to 0.01 for mostly-exponential, 
    large numbers like 100 for virtually linear): */	
    void setTargetRatioA(float targetRatio);
    void setTargetRatioDR(float targetRatio);
    
    // Reset the envelope generator:
    void reset(void);

    enum envState {
        env_idle = 0,
        env_attack,
        env_decay,
        env_sustain,
        env_release
    };

protected:
	int state;
	float output;
	float attackRate;
	float decayRate;
	float releaseRate;
	float attackCoef;
	float decayCoef;
	float releaseCoef;
	float sustainLevel;
    float targetRatioA;
    float targetRatioDR;
    float attackBase;
    float decayBase;
    float releaseBase;
 
    float calcCoef(float rate, float targetRatio);
};

inline float ADSR::process() {
	switch (state) {
        case env_idle:
            break;
        case env_attack:
            output = attackBase + output * attackCoef;
            if (output >= 1.0) {
                output = 1.0;
                state = env_decay;
            }
            break;
        case env_decay:
            output = decayBase + output * decayCoef;
            if (output <= sustainLevel) {
                output = sustainLevel;
                state = env_sustain;
            }
            break;
        case env_sustain:
            break;
        case env_release:
            output = releaseBase + output * releaseCoef;
            if (output <= 0.0) {
                output = 0.0;
                state = env_idle;
            }
	}
	return output;
}

inline void ADSR::gate(int gate) {
	if (gate)
		state = env_attack;
	else if (state != env_idle)
        state = env_release;
}

inline int ADSR::getState() {
    return state;
}

inline void ADSR::reset() {
    state = env_idle;
    output = 0.0;
}

inline float ADSR::getOutput() {
	return output;
}

#endif
