/*==============================================================================
 Interpolate.h  :   Jeff's (Juce) Audio ToolKit
 Created: 16 Mar 2015 7:50:07pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 ===============================================================================
 Array based classes:
                          OscLUT---SineLUT---AdditiveSineLUT
 CAArray--|--LookupTable_/
          |              l_SamplerLUT
          |
          |--Delay---MultiTapDelay
          |
          \-Interpolate   APFilter
           \             /
            CALattice---|-DiffDelay
                         \
                          CombFilter
 =============================================================================*/

#ifndef INTERPOLATE_H_INCLUDED
#define INTERPOLATE_H_INCLUDED

#include "CAArray.h"

namespace jATK
{
    class Interpolate : public CAArray
    {
    public:
        Interpolate();
        
    private:
    };
} // end namespace jATK



#endif  // INTERPOLATE_H_INCLUDED
