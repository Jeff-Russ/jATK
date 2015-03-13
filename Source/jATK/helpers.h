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

//namespace {
//    double TWOPI = 6.283185307179586476925286766559;
//    double PI = 6.283185307179586476925286766559 * 0.5;
//    float TWOPIf = 6.283185307179586476925286766559;
//    float PIf = 6.283185307179586476925286766559 * 0.5;
//}

namespace jATK
{
    /// typedefs: ==============================================================
    
    typedef float audio;

    ///  template inline functions: ============================================
    
    template<typename T> inline T clipMin (T inlet, T min = 0)
    {   if (inlet >= min) { return inlet; }
         else             { return min;   }
    }
    template<typename T> inline T clipMax (T inlet, T max)
    {   if (inlet <= max) { return inlet; }
         else             { return max;   }
    }
    template<typename T> inline T wrapMax (T inlet, T max)
    {   if (inlet <= max) { return inlet;       }
         else             { return inlet - max; }
    }
    template<typename T> inline T wrapMax (T inlet, T max, T size)
    {   if (inlet <= max) { return inlet;       }
         else             { return inlet - size; }
    }
    template<typename T> inline T wrapMin (T inlet, T size, T min = 0)
    {   if (inlet >= min) { return inlet;        }
         else             { return inlet + size; }
    }
    template<typename T> inline T hyperbolSat (T inlet, T L)
    {   if (inlet >= 0)
            return L - ( ( L / (L + abs(inlet)) ) * L );
         else
             return -(L - ( ( L / (L + abs(inlet)) ) * L ));
    }
    template<typename T> inline T polySat31 (T inlet, T L) /// UNFINISHED!!!
    {   T LMax = L * 1.5;                                  /// this should be
        T LMin = -LMax;                                    /// a class
        
        if (inlet > LMax)      { return L;  }
        else if (inlet < LMin) { return -L; }
        else 
    }
    ///  audio inline functions: ===============================================
    
    inline audio Interp4_AudioArr (audio index, audio iMinus1Sample, audio iSample,
                                   audio iPlus1Sample, audio iPlus2Sample )
    {   audio var1 = (iPlus1Sample - iMinus1Sample) * 0.5;
        audio var2 = iSample - iPlus1Sample;
        audio var3 = var1 + var2;
        audio var4 = var3 + ((iPlus2Sample - iSample) * 0.5);
        audio var5 = var4 + var2;
        audio var6 = ((index * var5) - var3 - var5) * index;
        return (var6 + var1) * index + iSample;
    }
    //== Mathematics: ==========================================================
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
    inline audio wrap1 (audio phase)   { return fmodf(phase, 1.0); }
    //==========================================================================
    inline audio ratio1 (audio phase, audio ratio)
    {   return fmodf((phase * ratio), 1.0);
    }
    //==========================================================================
    inline audio phaseDistort (audio phase, audio knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5f;
         else return ( (1 / (1 - knee)) * (phase - knee) * 0.5f ) + 0.5f;
    }
} // end namespace jATK
#endif  // INLINE_H_INCLUDED
