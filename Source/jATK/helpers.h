/*==============================================================================
 helpers.h  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Mar 2015 2:22:45pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <cmath>

namespace jATK
{
    /// typedefs: ==============================================================
    typedef float Audio;
    typedef float AudioHQ;
    typedef double PreAudio;
    
    /// constants: ==============================================================
    const Audio ZERO_A = 0.0;
    const Audio ONE_A = 1.0;
    const Audio FIVE_A = 5.0;
    const Audio TWOPI_A = 6.283185307179586476925286766559;
    const Audio PI_A = 6.283185307179586476925286766559 * 0.5;
    const PreAudio ZERO_PA = 0.0;
    const PreAudio TWOPI_PA = 6.283185307179586476925286766559;
    const PreAudio PI_PA = 6.283185307179586476925286766559 * 0.5;

    ///  template inline functions: ============================================
    template<typename T> inline T clipMin (T inlet, T min = 0)
    {   if (inlet >= min) { return inlet; }
         else             { return min;   }
    }
    template<typename T> inline T DNC (T inlet) // denormal number cancel
    {   if (! (inlet < -1.0e-8 || inlet > 1.0e-8)) return 0;
         else return inlet;
    }
    template<typename T> inline T clipMax (T inlet, T max = 1)
    {   if (inlet <= max) { return inlet; }
         else             { return max;   }
    }
    template<typename T> inline T clipMinMax (T inlet, T min, T max = ONE_A)
    {   if (inlet <= max && inlet >= min) { return inlet; }
        else if ( inlet > max)            { return max;   }
        else                              { return min;   }
    }
    template<typename T> inline T wrapMax (T inlet, T max)
    {   if (inlet <= max) { return inlet;       }
         else             { return inlet - max; }
    }
    template<typename T> inline T wrapMax (T inlet, T max, T size)
    {   if (inlet <= max) { return inlet;        }
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
    template<typename T> inline T CltrShaper (T inlet, T one, T half, T zero)
    {   if (inlet >= 0.0)
            return (one - half) * 2.0 * (inlet - 0.5) + half;
        else
            return (half - zero) * 2.0 * inlet + zero;
    }
    template<typename T> inline T dB2AF (T inlet)
    {   return pow(1.12202, inlet);
    }
    //    template<typename T> class polySat31
    
    ///  Audio inline functions: ===============================================
    inline Audio interpolate4 (Audio index, Audio iMinus1Sample, Audio iSample,
                                   Audio iPlus1Sample, Audio iPlus2Sample )
    {   Audio var1 = (iPlus1Sample - iMinus1Sample) * 0.5;
        Audio var2 = iSample - iPlus1Sample;
        Audio var3 = var1 + var2;
        Audio var4 = var3 + ((iPlus2Sample - iSample) * 0.5);
        Audio var5 = var4 + var2;
        Audio var6 = ((index * var5) - var3 - var5) * index;
        return (var6 + var1) * index + iSample;
    }
    inline Audio xFade (Audio x, Audio in0, Audio in1)
    {   return ( (1 - x) * in0 ) + (x * in1);
    }
    //== Mathematics: ==========================================================
    inline Audio sine4 (Audio phase)
    {   float absPh = fabs(phase);
        return (phase * 68.5949) * (absPh + 0.232963) *
        (absPh - 0.5)  * (absPh - 0.732963);
    }
    inline Audio sine8 (Audio phase)
    {   double absPh = fabs(phase);
        return phase *  60.2522 * ((absPh * (absPh + 1.05802)) + 0.436501) *
        (absPh + 0.424933) * ((absPh * (absPh - 2.05802)) + 1.21551) *
        (absPh - 0.5) * (absPh - 0.924933);
    }
    //==========================================================================
    inline Audio wrap1 (Audio phase)   { return fmodf(phase, 1.0); }
    //==========================================================================
    inline Audio ratio1 (Audio phase, Audio ratio)
    {   return fmodf((phase * ratio), 1.0);
    }
    //==========================================================================
    inline Audio phaseDistort (Audio phase, Audio knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5f;
         else return ( (1 / (1 - knee)) * (phase - knee) * 0.5f ) + 0.5f;
    }
} // end namespace jATK
#endif  // INLINE_H_INCLUDED
