/*==============================================================================
 AHDSR.h  :   Jeff's (Juce) Audio ToolKit
 Created: 12 Apr 2015 7:26:18pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

///  THIS FILE IS NOT NEARLY COMPLETE ========================================


#ifndef AHDSR_H_INCLUDED
#define AHDSR_H_INCLUDED

#include <cmath>
#include "helpers.h"

namespace jATK
{
    class AHDSR // analog capacitor based envelope emulation from Reaktor
    {           // original module "AHDSR Capacitor V3.4"
        Audio sr, onV, offV, a, a1, h = 0, d, s = 0, r, vc, vGate; 
        Audio up = 0, tau = 0, z = 0, incr, coef, adder, output;
        int rm, sI, upI = 0;
        void updateCircuit()
        {   adder = pow ( 2.71828f, 1 / tau * sr * -5.f ); coef = 1 - adder; }
        void delaySustain()
        {   vGate = onV; tau = d; sI = 1; updateCircuit(); }
    public:
        AHDSR (Audio sRate) { sr = sRate; }
        void set (Audio attack, Audio hold, Audio decay, Audio sustain,
                  Audio release, int retrigMode = 0)
        {   this->attack (attack); this->hold (hold); this->decay (decay);
            this->sustain (sustain); this->release (release);
            this->retrig (retrigMode);
        }
        void setSRate (Audio sRate)  { sr = sRate; } // set sample rate
        void attack (Audio seconds)                  // set attack in seconds
        {   a = seconds; this->setOn(); } 
        void hold (Audio seconds)                    // set hold time in seconds
        {   h = seconds; this->setOn(); }
        void decay (Audio seconds)                   // set decay in seconds
        {   d = clipMin (seconds, Audio(1E-012));
            if (sI == 1) { this->delaySustain(); }
        }
        void sustain (Audio zeroTo1)                // set sustain level 0...1
        {   s = clipMinMax (zeroTo1, ZERO_A);
            if (sI == 1) { this->delaySustain(); }
        }
        void release (Audio seconds)               // set release in seconds
        {   r = clipMin (seconds, Audio (1E-012));
            if (sI == 0) { this->setOff(); }
        }                     // set retrigger mode:      0 = analog retrigger
        void retrig (int zeroTo3)  // 1 = analog legato   2 = digital retrigger
        {   rm = clipMinMax (zeroTo3, 0, 3); }     //     3 = digital legato
        Audio noteOn()
        {   onV = vGate;
            if (  ((rm & 1) == 0)  ||  (sI == 0)   )
            {   a = vGate;
                if (rm & 2) { z = 0.f; } // this might have to happen later
                this->setOn();
            }
            if ( (up + incr) >= 1) // advance location
            {   if (++upI > 1 && s == 1) { delaySustain(); } }
            z = output = vGate * coef + adder;// process output
            return output;
        }
        Audio noteOff()
        {   offV = vGate; this->setOff();
            z = output = vGate * coef + adder; // process output
            return output;
        }
        void setOn()
        {   up = 0.f; upI = 0; vGate = onV;
            tau = a1 = (1 - z / onV) * a;
            incr = 1 / (a1 + h) * sr;
            this->updateCircuit();
        }
        void setOff() { vGate = 0; tau = r; sI = 0; updateCircuit(); }
    };
} // end namespace jATK
#endif  // AHDSR_H_INCLUDED
