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
    
    class Shaper123
    {
        Shaper123 (Audio sRate, Audio one, Audio two, Audio three)
        {   Filter1p filter (sRate, Audio(5) ); // this line gets error
            _1 = one; _2 = two; _3 = three;
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

} // end namespace jATK
#endif  // SHAPER123_H_INCLUDED
