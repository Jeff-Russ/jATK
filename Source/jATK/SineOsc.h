/*==============================================================================
 SineOsc.h  :   Jeff's (Juce) Audio ToolKit
 Created: 28 Apr 2015 11:28:50am
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef SINEOSC_H_INCLUDED
#define SINEOSC_H_INCLUDED

#include "helpers.h"
#include "LUT.h"

namespace jATK
{
    class SineOsc
    {
        bool big, flip; double outd; float outf;
        
    public:
        SineOsc (bool bigLut) : big(bigLut) {}
        
        double operator()(double phase)
        {
        }
        
        float operator()(float phase)
        {

        }
        
        
    };
    
} // end namespace jATK

#endif  // SINEOSC_H_INCLUDED
