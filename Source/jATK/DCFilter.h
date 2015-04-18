/*==============================================================================
 DCFilter.h  :   Jeff's (Juce) Audio ToolKit
 Created: 10 Apr 2015 12:46:44am
  Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

/// this file is nearly complete but needs separate implementation and testing

#ifndef DCFILTER_H_INCLUDED
#define DCFILTER_H_INCLUDED

namespace jATK
{

    class DCFilter  // do to: add DNC to both in and prevOut
    {   Audio outlet, prevIn = 0.0, prevOut = 0.0;
    public:
        Audio operator() (Audio in)
        {   outlet = DNC( (prevOut * 0.9999) + (in - prevIn) );
            prevIn = in; prevOut = outlet;
            return outlet;
        }
    };


} // end namespace jATK

#endif  // DCFILTER_H_INCLUDED
