/*==============================================================================
 helpers.h  :   Jeff's (Juce) SNum ToolKit
 Created: 8 Mar 2015 2:22:45pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

///  this file is nearly complete but needs testing ===========================

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
    template<typename SNum> inline SNum clipMin (SNum inlet, SNum min = 0)
    {   if (inlet >= min) { return inlet; }
         else             { return min;   }
    }
    template<typename SNum> inline SNum DNC (SNum inlet) // denormal number cancel
    {   if (! (inlet < -1.0e-8 || inlet > 1.0e-8)) return 0;
         else return inlet;
    }
    template<typename SNum> inline SNum clipMax (SNum inlet, SNum max = 1)
    {   if (inlet <= max) { return inlet; }
         else             { return max;   }
    }
    template<typename SNum> inline SNum clipMinMax (SNum inlet, SNum min,
                                                    SNum max = ONE_A)
    {   if (inlet <= max && inlet >= min) { return inlet; }
        else if ( inlet > max)            { return max;   }
        else                              { return min;   }
    }
    template<typename SNum> inline SNum wrapMax(SNum inlet, SNum max)
    {   if (inlet <= max) { return inlet;       }
         else             { return inlet - max; }
    }
    template<typename SNum> inline SNum wrapMax (SNum inlet, SNum max,
                                                 SNum size)
    {   if (inlet <= max) { return inlet;        }
         else             { return inlet - size; }
    }
    template<typename SNum> inline SNum wrapMin (SNum inlet, SNum size,
                                                 SNum min = 0)
    {   if (inlet >= min) { return inlet;        }
         else             { return inlet + size; }
    }
    template<typename SNum> inline SNum hyperbolSat (SNum inlet, SNum L)
    {   if (inlet >= 0)
            return L - ( ( L / (L + abs(inlet)) ) * L );
        else
            return -(L - ( ( L / (L + abs(inlet)) ) * L ));
    }
    template<typename SNum> inline SNum CltrShaper (SNum inlet, SNum one,
                                                    SNum half, SNum zero)
    {   if (inlet >= 0.0)
            return (one - half) * 2.0 * (inlet - 0.5) + half;
        else
            return (half - zero) * 2.0 * inlet + zero;
    }
    template<typename SNum> inline SNum dB2AF(SNum inlet)
    {   return pow(1.12202, inlet);
    }
    template<typename SNum> inline SNum xFade (SNum x, SNum in0, SNum in1)
    {   return ( (1 - x) * in0 ) + (x * in1);
    }
    //    template<typename T> class polySat31
    
    //== interpolation =================================================
    template<typename SNum> inline SNum interpolate4 (SNum index,
    SNum iMinus1Sample, SNum iSample, SNum iPlus1Sample, SNum iPlus2Sample )
    {   SNum var1 = (iPlus1Sample - iMinus1Sample) * 0.5;
        SNum var2 = iSample - iPlus1Sample;
        SNum var3 = var1 + var2;
        SNum var4 = var3 + ((iPlus2Sample - iSample) * 0.5);
        SNum var5 = var4 + var2;
        SNum var6 = ((index * var5) - var3 - var5) * index;
        return (var6 + var1) * index + iSample;
    }
    //== sine ==========================================================
    template<typename SNum> inline SNum sine4 (SNum phase)
    {   float absPh = fabs(phase);
        return (phase * 68.5949) * (absPh + 0.232963) *
        (absPh - 0.5)  * (absPh - 0.732963);
    }
    template<typename SNum> inline SNum sine8 (SNum phase)
    {   double absPh = fabs(phase);
        return phase *  60.2522 * ((absPh * (absPh + 1.05802)) + 0.436501) *
        (absPh + 0.424933) * ((absPh * (absPh - 2.05802)) + 1.21551) *
        (absPh - 0.5) * (absPh - 0.924933);
    }
    //=======================================================================
    template<typename SNum> inline SNum wrap1 (SNum phase)
    {   return fmodf(phase, 1.0); }
    //=======================================================================
    template<typename SNum> inline SNum ratio1 (SNum phase, SNum ratio)
    {   return fmodf((phase * ratio), 1.0); }
    //=======================================================================
    template<typename SNum> inline SNum phaseDistort (SNum phase, SNum knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5f;
         else return ( (1 / (1 - knee)) * (phase - knee) * 0.5f ) + 0.5f;
    }
    
    
    ///  template classes: =================================================
    //-- Slew --------------------------------------------------------------
    template <class SNum> class Slew
    { public:
        Slew (SNum init, SNum adder = 0.001, SNum subt = 0.001)
        : add(adder),sub(subt), internal(init), prevIn(init), output(init){}
        
        void reset (SNum init) { output = prevIn = internal = init; }
        
        void set (SNum adder, SNum subt) {add = adder; sub = subt; }
        
        SNum operator()(SNum input)
        {   this->input = input;
            if (input != output)
            {   // determine direction only upon new input value:
                if (input != prevIn) { this->calc(input); }
                this->process(input); // process input
            } // else we will use the previous output
            return output;
        }
        bool notArrived() { return input != output; }
        
    protected:
        void calc (SNum input)
        {   diff = input - internal;  // want to find difference and
            if (diff > 0) { goUp = true; }  // determine direction.
        }
        void process(SNum input)
        {   if (goUp)   // process rising output
        {   if (internal < input) { output = internal = internal + add; }
        else { output = internal = input; } // went too far. set to goal.
        }else       // process falling output
        {   if (internal > input) { output = internal = internal - sub; }
        else { output = internal = input; } // went too far. set to goal.
        }
        }
        SNum add, sub, diff, internal; bool goUp;
    protected:
        SNum prevIn, output, input;
    };
    //-- SlewLimiter -----------------------------------------------------------
    template <class SNum> class SlewLimiter : public Slew<SNum>
    { public:
        SlewLimiter (SNum sRate, SNum initValue = 0.f) : Slew<SNum>(initValue)
        { msPerSample = 1000 / sRate; }
        void setSRate (SNum sRate) { msPerSample = 1000 / sRate; }
        void set (SNum upMsPer1, SNum dnMsPer1)
        {   this->addsub (upMsPer1, dnMsPer1); }
    protected:
        void addsub(SNum upMsPer1, SNum dnMsPer1)
        {   Slew<SNum>::add = msPerSample / upMsPer1;
            Slew<SNum>::sub = msPerSample / dnMsPer1;
        }
        SNum msPerSample;
    };
    //-- LinearRamp -----------------------------------------------------------
    template <class SNum> class LinearRamp : public SlewLimiter<SNum>
    { public:
        LinearRamp (SNum sRate, SNum initValue) : SlewLimiter<SNum>(sRate,initValue)
        {}
        void set (SNum upMs, SNum dnMs) { this->upMs = upMs; this->dnMs = dnMs; }
        void calc (SNum input)
        {   diff = input - Slew<SNum>::internal;
            if (diff > 0) { Slew<SNum>::goUp = true; }
            Slew<SNum>::add =       diff  * SlewLimiter<SNum>::msPerSample / upMs;
            Slew<SNum>::sub = fabsf(diff) * SlewLimiter<SNum>::msPerSample / dnMs;
        }
    private:
        SNum upMs, dnMs, diff;
    };
    //-- PeakDetector -----------------------------------------------------------
    template <class SNum> class PeakDetector : public SlewLimiter<SNum>
    { public:
        PeakDetector<SNum> (SNum sRate) : SlewLimiter<SNum>(sRate, 0.0)
        {   SlewLimiter<SNum>::set (0.6f, 50); }
        SNum operator()(SNum input) {return SlewLimiter<SNum>::operator() (fabs(input));}
    };
    //    class NonlinearRamp : public Slew
} // end namespace jATK
#endif  // INLINE_H_INCLUDED
