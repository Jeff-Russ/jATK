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
        PhaseDistort (Audio breakPoint){ bp = breakPoint; bpRecip = 1 / bp; }
        Audio operator()(Audio inlet)
        {
            if (inlet > bp) { return bpRecip / inlet / 2; }
            else { return ((((inlet - bp) * (1 / (1 - bp))) / 2) + 0.5); }
        }
        Audio operator()(Audio inlet, Audio breakPoint)
        {
            bp = breakPoint; bpRecip = 1 / bp;
            this->operator()(inlet);
        }
    };
    // [expr~ if($v1<$v2, ($v1*(1/$v2))/2, ((($v1-$v2)*(1/(1-$v2)))/2)+0.5)]
} // end namespace jATK

#endif  // PHASEDISTORT_H_INCLUDED
