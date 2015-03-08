/*
  ==============================================================================

    Interpolate.h
    Created: 8 Mar 2015 12:46:12pm
    Author:  Jeff-Russ

  ==============================================================================
*/

#ifndef INTERPOLATE_H_INCLUDED
#define INTERPOLATE_H_INCLUDED

namespace jATK
{
    ///=========================================================================

inline float Interp4_fArray (float index,
                             float iMinus1Sample,
                             float iSample,
                             float iPlus1Sample,
                             float iPlus2Sample )
    {
        var1 = (iPlus1Sample - iMinus1Sample) * 0.5;
        var2 = iSample - iPlus1Sample;
        var3 = var1 + var2;
        var4 = var3 + ((iPlus2Sample - iSample) * 0.5);
        var5 = var4 + var2;
        var6 = ((index * var5) - var3 - var5) * index;
        
        return (var6 + var1) * index + iSample;
    }
    



    ///=========================================================================
    
} // end namespace jATK
#endif  // INTERPOLATE_H_INCLUDED
