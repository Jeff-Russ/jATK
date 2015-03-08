/*
 ==============================================================================
 
 helpers.h
 Created: 8 Mar 2015 2:22:45pm
 Author:  Jeff-Russ
 
 ==============================================================================
 */

#ifndef INLINE_H_INCLUDED
#define INLINE_H_INCLUDED

#include <cmath>

namespace jATK
{
    /// typedefs: ==============================================================
    
    typedef float audio;
    
    /// inline functions: ======================================================
    
    inline audio audioClip0 (audio inlet)
    {   if (inlet >= 0.0) { return inlet;}
    else              { return 0.0;  }
    }
    //==========================================================================
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
    //==========================================================================
    inline audio sine4 (audio phase)
    {   float absPh = fabs(phase);
        return (phase * 68.5949) * (absPh + 0.232963) *
        (absPh - 0.5)  * (absPh - 0.732963);
    }
    inline audio sine8 (audio phase)
    {   double absPh = fabs(phase);
        return phase *  60.2522 * ((absPh * (absPh + 1.05802)) + 0.436501) *
        (absPh + 0.424933) * ((absPh * (absPh - 2.05802)) + 1.21551) *
        (absPh - 0.5) * (absPh - 0.924933);
    }
    //==========================================================================
    inline float wrap1 (float phase)
    {   return fmodf(phase, 1.0f);
    }
    inline double wrap1 (double phase)
    {   return fmodf(phase, 1.0);
    }
    //==========================================================================
    inline float ratio1 (float phase, float ratio)
    {   return fmodf((phase * ratio),1.0f);
    }
    inline float ratio1 (float phase, double ratio)
    {   return fmodf((phase * (float)ratio),1.0f);
    }
    inline double ratio1 (double phase, double ratio)
    {   return fmodf((phase * ratio),1.0);
    }
    //==========================================================================
    inline float phaseDistort (float phase, float knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5f;
    else return ( (1 / (1 - knee)) * (phase - knee) * 0.5f ) + 0.5f;
    }
    inline double phaseDistort (double phase, double knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5;
    else return ( (1 / (1 - knee)) * (phase - knee) * 0.5 ) + 0.5;
    }
    ///=========================================================================
    
    /// Classes: ===============================================================
    
    class BoundsClipper
    {
        int max;
        int min;
        // UNFINISHED
    };
    
    
} // end namespace jATK





#endif  // INLINE_H_INCLUDED
