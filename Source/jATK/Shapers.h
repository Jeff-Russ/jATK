/*==============================================================================
 Shaper123.h  :   Jeff's (Juce) Audio ToolKit
 Created: 10 Apr 2015 2:16:57pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef SHAPER123_H_INCLUDED
#define SHAPER123_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    class Filter1p
    { public:
        Filter1p (Audio sRate, Audio cutFreq)
        {   this->setSRate(sRate);
            this->setCut(cutFreq);
        };
        void setSRate (Audio sRate) { sr2Pi = 6.28 * sRate; calc();        }
        void setCut (Audio cutFreq) { cut = cutFreq; this->calc();         }
        Audio hpf(Audio inlet)      { this->process (inlet); return hpOut; }
        Audio lpf(Audio inlet)      { this->process (inlet); return lpZ;   }
    private:
        void process(Audio inlet){hpOut = inlet - lpZ; lpZ = hpOut * coef + lpZ;}
        void calc() { coef = clipMax (sr2Pi * cut); }
        Audio cut, sr2Pi, coef, hpOut, lpZ = 0;
    };
    
    class Shaper123  // Provides controllable shaping of 2nd and 3rd order
    {  public:
        Shaper123 (Audio sRate, Audio clean, Audio firstOrder, Audio thirdOrder)
        {   Filter1p filter (sRate, FIVE_A ); // this line gets error
            _1 = clean; _2 = firstOrder; _3 = thirdOrder;
        }
        void setShape (Audio clean, Audio firstOrder, Audio thirdOrder)
        {   _1 = clean;        // Non distorted signal amount
            _2 = firstOrder;   // Second order distortion amount
            _3 = thirdOrder;   // Third order distortion amount
        }
        void setSRate (Audio sRate) { filter.setSRate (sRate); }
        
        Audio operator()(Audio inlet)
        {   inX2 = inlet * 2;
            outlet = inX2 * inlet * _3;
            outlet += filter.hpf(inX2) * _2  + _1 * inlet;
            return outlet;
        }
        
      private:
        Audio inX2, _1, _2, _3, outlet;
        Filter1p filter;
    };
    class Shaper312 // Shaper with variable amount of 2nd or 3rd order shaping
    {   
        Shaper312 (Audio sRate, Audio shape)
        {   Filter1p filter (sRate, FIVE_A ); // this line gets error
            shp = shape; shpAbs = fabs(shp);
        }
        void setShape (Audio shape)
        {                   // shape = 0 = no shaping
            shp = shape;    // shape > 0 = 3rd order shaping
        }                   // shape < 0 = 2nd order shaping
        void setSRate (Audio sRate) { filter.setSRate (sRate); }
        
        Audio operator()(Audio inlet)
        {   inX2 = inlet * 2;
            if (inlet > 0)
                outlet = inlet * inX2 * shpAbs;
            else
                outlet = filter.hpf(inX2) * shpabs;
            return outlet;
        }
        
    private:
        Audio inX2, shp, shpAbs outlet;
        
} // end namespace jATK
#endif  // SHAPER123_H_INCLUDED
