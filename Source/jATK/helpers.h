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
    
    /// overloaded inline functions: ===========================================
    
    inline audio audioClip0 (audio inlet)  /// deprecated for template version
    {   if (inlet >= 0.0) { return inlet; }
         else             { return 0.0;   }
    }
    inline audio audioClipMin (audio inlet, audio min = -1.0) /// deprecated for template version
    {   if (inlet >= min) { return inlet; }
         else             { return min;   }
    }
    inline audio audioClipMax (audio inlet, audio max = 1.0) /// deprecated for template version
    {   if (inlet <= max) { return inlet; }
         else             { return max;   }
    }
    inline int intClipMin (int inlet, int min = 0) /// deprecated for template version
    {   if (inlet >= min) { return inlet; }
         else             { return min;   }
    }
    inline int intClipMax (int inlet, int max) /// deprecated for template version
    {   if (inlet <= max) { return inlet; }
         else             { return max;   }
    }
    inline int intWrapMin (int inlet, int size, int min = 0) /// deprecated for template version
    {   if (inlet >= min) { return inlet;        }
         else             { return inlet + size; }
    }
    inline int intWrapMax (int inlet, int max, int size) /// deprecated for template version
    {   if (inlet <= max) { return inlet;        }
         else             { return inlet - size; }
    }
    inline int intWrapMax (int inlet, int max) /// deprecated for template version
    {   if (inlet <= max) { return inlet;       }
         else             { return inlet - max; }
    }
    /// template inline functions: ============================================
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
    //==========================================================================
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
    inline float wrap1 (float phase)   { return fmodf(phase, 1.0f); }
    inline double wrap1 (double phase) { return fmodf(phase, 1.0);  }
    inline int wrapIndex (int inlet, int size)
    {   if (inlet < size) { return inlet; }
    else { return inlet - size; }
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
    // UNFINISHED
} // end namespace jATK
#endif  // INLINE_H_INCLUDED
