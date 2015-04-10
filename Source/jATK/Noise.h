/*==============================================================================
 DCFilter.h  :   Jeff's (Juce) Audio ToolKit
 Created: 10 Apr 2015 12:46:44am
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef NOISE_H_INCLUDED
#define NOISE_H_INCLUDED

#include "helpers.h"

namespace jATK
{

class DigitalNoise
{   int internal;
    Audio temp;
  public:
    DigitalNoise (int seed) { internal = seed; }
    
    Audio operator()()
    {   return ( (Audio)(internal * 1103515245 + 12345) ) * 4.6567E-10;
    }
    Audio binary()
    {   temp = this->();
        if (temp > 0) return 0.5;
        else          return -0.5;
        
    }
    Audio seed (int seed) { internal = seed; }
};

} // end namespace jATK

#endif  // NOISE_H_INCLUDED
