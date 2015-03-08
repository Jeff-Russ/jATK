/*
 ==============================================================================
 
 Interpolate.h
 Created: 8 Mar 2015 12:46:12pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#ifndef INTERPOLATE_H_INCLUDED
#define INTERPOLATE_H_INCLUDED

#include "types.h"

namespace jATK
{
    ///=========================================================================
    
    inline audio Interp4_fArray (audio index,
                                 audio iMinus1Sample,
                                 audio iSample,
                                 audio iPlus1Sample,
                                 audio iPlus2Sample )
    {
        audio var1 = (iPlus1Sample - iMinus1Sample) * 0.5;
        audio var2 = iSample - iPlus1Sample;
        audio var3 = var1 + var2;
        audio var4 = var3 + ((iPlus2Sample - iSample) * 0.5);
        audio var5 = var4 + var2;
        audio var6 = ((index * var5) - var3 - var5) * index;
        
        return (var6 + var1) * index + iSample;
    }
    
    
} // end namespace jATK
#endif  // INTERPOLATE_H_INCLUDED
