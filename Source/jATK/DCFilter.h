/*==============================================================================
 DCFilter.h  :   Jeff's (Juce) Audio ToolKit
 Created: 10 Apr 2015 12:46:44am
  Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/


#ifndef DCFILTER_H_INCLUDED
#define DCFILTER_H_INCLUDED

class DCFilter  // do to: add DNC to both in and prevOut
{   Audio out, prevIn = 0.0, prevOut = 0.0;
public:
    Audio operator() (Audio in)
    {   out = (prevOut * 0.9999) + (in - prevIn);
        prevIn = in; prevOut = out;
        return out;
    }
};



#endif  // DCFILTER_H_INCLUDED
