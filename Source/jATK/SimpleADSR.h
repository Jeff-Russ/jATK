/*==============================================================================
 SimpleADSR.h  :   Jeff's (Juce) Audio ToolKit
 Created: 10 Apr 2015 3:59:25pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 based on a Reaktor Core module by salamanderanagram
 =============================================================================*/

#ifndef SIMPLEADSR_H_INCLUDED
#define SIMPLEADSR_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    class SimpleADSR
    {
    public:
        SimpleADSR (Audio sRate) {sr = sRate; } // constructor
        
        void set (Audio att, Audio dec, Audio sus, Audio rel,
                  bool legato, Audio sRate)
        {   sr = sRate; s = sus; l = legato;
            this->attack (att);
            this->decay  (dec);
            this->release(rel);
        }
        void veloGate(Audio veloGate) // new note
        {   if (veloGate > ZERO_A)   // SET GATE BOOL HERE
            gateOn = true;
            g = veloGate; upL = veloGate; dnL = veloGate * s;
            if (gateOn) { up = 1;  dnT = b1; }
            else      { upT = 0; dnT = b0; }
        }
        Audio operator()() // process sample
        {
            if (!l)
            {   if (gateOn ) { upMode = true;  }
                else         { upMode = false; }
            }
            
        }
        void attack  (Audio att) { upT =time2CoefL(att); }
        void decay   (Audio dec) { b1 = time2CoefX(dec); }
        void sustain (Audio sus) { s = sus; }
        void release (Audio rel) { b0 = time2CoefX(rel); }
        void legato  (Audio leg) { l = leg; }
        
    private:
        Audio g, sr, upL, dnL, z = 0, upT, dnT, up, a, d, s, r, l, b1, b0;
        bool attMode, gateOn, prevGate = false, upMode;
        
        Audio time2CoefL (Audio tExp)
        {   return ONE_A / (clipMin( dB2AF(tExp) * sr * 0.001) , ONE_A);
        }
        Audio time2CoefX (Audio tExp)
        {   return ONE_A / (clipMin( dB2AF(tExp) * sr * 0.000693147), ONE_A);
        }
        Audio upLinear()
        {   up = z + upT;
            if (up < upL) { return up;  }
            else          { return upL; }
        }
        Audio dnExpon()
        {   return (dnL - z) * dnT + z;
        }
    };
    
} // end namespace jATK
#endif  // SIMPLEADSR_H_INCLUDED
