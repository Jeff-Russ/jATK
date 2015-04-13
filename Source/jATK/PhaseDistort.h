/*==============================================================================
PhaseDistort.h  :   Jeff's (Juce) Audio ToolKit
Created: 12 Apr 2015 5:23:21pm
Author:  Jeff-Russ     https://github.com/Jeff-Russ
=============================================================================*/


#ifndef PHASEDISTORT_H_INCLUDED
#define PHASEDISTORT_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    // this class might have denormal num or div/0 issues
    class PhaseDistort
    {
    private:
        Audio bp, bpRecip;
    public:
        PhaseDistort (Audio knee)
        {   bp = clipMinMax (knee, 0.00001f, 0.999999f);
            bpRecip = 1 / bp; 
        }
        Audio operator()(Audio phase)
        {   if (phase < bp) return (bpRecip)* phase * 0.5f;
            else return ((1 / (1 - bp)) * (phase - bp) * 0.5f) + 0.5f;
        }
        Audio operator()(Audio phase, Audio knee)
        {   bp = clipMinMax (knee, 0.00001f, 0.999999f);
            bpRecip = 1 / bp;
            this->operator()(phase);
        }

        inline Audio phaseDistort (Audio phase, Audio knee)
        {   if (phase < knee) return (bpRecip) * phase * 0.5f;
            else return ((1 / (1 - knee)) * (phase - knee) * 0.5f) + 0.5f;
        }
    };
    // [expr~ if($v1<$v2, ($v1*(1/$v2))/2, ((($v1-$v2)*(1/(1-$v2)))/2)+0.5)]
} // end namespace jATK

#endif  // PHASEDISTORT_H_INCLUDED
