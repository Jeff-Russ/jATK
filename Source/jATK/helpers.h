/*==============================================================================
 helpers.h  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Mar 2015 2:22:45pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/
#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <cmath>

namespace
{   double TWOPI = 6.283185307179586476925286766559;
    double PI = 6.283185307179586476925286766559 * 0.5;
    float TWOPIf = 6.283185307179586476925286766559;
    float PIf = 6.283185307179586476925286766559 * 0.5;
}

namespace jATK
{
    /// typedefs: ==============================================================
    typedef float audio;
    typedef float audioHQ;
    typedef double preAudio;

    ///  template inline functions: ============================================
    template<typename T> inline T clipMin (T inlet, T min = 0)
    {   if (inlet >= min) { return inlet; }
         else             { return min;   }
    }
    template<typename T> inline T clipMax (T inlet, T max)
    {   if (inlet <= max) { return inlet; }
         else             { return max;   }
    }
    template<typename T> inline T clipMinMax (T inlet, T min, T max)
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
    //    template<typename T> class polySat31
    
    /// classes: ===============================================================
    class FilterCut
    { public:
        FilterCut()
        {   this->setSampleRate(44100.0);
        }
        void setSampleRate (preAudio sampleRate)
        {   sr = sampleRate;
            max = sr / 24576;
            min = sr / 2.125;
            srPi = PI * sr;
        }
        preAudio clipFreq (preAudio freq)
        {   return clipMinMax (freq, min, max);
        }
        preAudio preWarp (preAudio freq)
        {   return tan(freq + srPi);
        }
        preAudio getW (preAudio freq)
        {   return this->preWarp(this->clipFreq(freq));
        }
      private:
        preAudio sr, max, min, srPi;
    };
    class BiLinIn1
    { public:
        BiLinIn1 ()
        {   x1 = 0;
        }
        void setCoeff (audio a1, audio b0, audio b1)
        {   this->a1 = a1;
            this->b0 = b0;
            this->b1 = b1;
        }
        audio process (audio audioIn)
        {   result = (x1 * b1) + (audioIn * b0) + (result * a1);
            x1 = audioIn;
            return result;
        }
        audio process (audio audioIn, audio a1, audio b0, audio b1)
        {   this->setCoeff(a1, b0, b1);
            return this->process (audioIn);
        }
      private:
        audio result, x1, a1, b0, b1;
    };
    class BiQuadIn
    { public:
        BiQuadIn ()
        {   x1 = 0; x2 = 0; y1 = 0; y2 = 0;
        }
        void setCoeff (audio a0, audio a1, audio a2, audio a3, audio a4)
        {   this->a0 = a0;
            this->a1 = a1;
            this->a2 = a2;
            this->a3 = a3;
            this->a4 = a4;
        }
        audio process (audio audioIn)
        {   result = a0 * audioIn + a1 * x1 + a2 * x2 - a3 * y1 - a4 * y2;
            x2 = x1;        // shift x1 to x2, sample to x1 
            x1 = audioIn;
            y2 = y1;        // shift y1 to y2, result to y1
            y1 = result;
            return result;
        }
        audio process (audio audioIn,
                       audio a0, audio a1, audio a2, audio a3, audio a4)
        {   this->setCoeff (a0, a1, a2, a3, a4);
            return this->process (audioIn);
        }
    private:
        audio a0, a1, a2, a3, a4, result, x1, x2, y1, y2;
    };
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
