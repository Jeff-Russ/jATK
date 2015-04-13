/*==============================================================================
 AHDSR.h  :   Jeff's (Juce) Audio ToolKit
 Created: 12 Apr 2015 7:26:18pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
=============================================================================*/


#ifndef AHDSR_H_INCLUDED
#define AHDSR_H_INCLUDED

#include <cmath>
#include "helpers.h"

namespace jATK
{
    class AHDSR // analog capacitor based envelope emulation from Reaktor
    {           // original module "AHDSR Capacitor V3.4"
        Audio sr, a, h = 0, d, s = 0, r, vc, vin, tau, z = 0, ssA;
        int rm, sI, ssI;
    public:
        AHDSR (Audio sRate) { sr = sRate; }
        void set (Audio attack, Audio hold, Audio decay, Audio sustain,
                  Audio release, int retrigMode = 0)
        {   this->attack (attack); this->hold (hold); this->decay (decay);
            this->sustain (sustain); this->release (release); 
            this->retrig (retrigMode); 
        }
        void setSRate (Audio sRate)  { sr = sRate; }
        void attack (Audio seconds) { a = seconds; }
        void hold (Audio seconds) { h = seconds;  }
        void decay (Audio seconds) { d = clipMin (seconds, Audio(1E-012)); }
        void sustain (Audio zeroTo1) { s = clipMinMax (zeroTo1, ZERO_A); }
        void release (Audio seconds) { r = clipMin (seconds, Audio (1E-012)); }
        void retrig (int zeroTo3) { rm = clipMinMax(zeroTo3, 0, 3); }
        Audio on (){}
        Audio off (){}

    private:
        Audio a1, a2, a3;
        
        Audio rcEnv()
        {   a1 = pow ( 2.71828f, 1 / tau * sr * -5.f );
            a2 = vin * (1 - a1);
            a3 = a1 * z;
            z = a2 + a3;
            return z;
        }
        void gate(Audio GVel)
        {   if (GVel)
            {   if (  ((rm & 1) == 0)  ||  (sI == 0)   )
                vin = GVel;
                this->attackHold();
            }else { this->release(); }
        }
        void attackHold()
        {   ssA = 0.f; ssI = 0;
            tau = (1 - z / vin) * a;
            incr = 1 / ((tau + h) * sr)
            
        }
        void delaySustain()
        {
            
        }
        void release()
        {
            
        }
    };
} // end namespace jATK
#endif  // AHDSR_H_INCLUDED
