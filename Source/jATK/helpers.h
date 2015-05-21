/*==============================================================================
 helpers.h  :   Jeff's (Juce) Audio ToolKit
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
    const Audio TAU_A = 6.283185307179586476925286766559005768394338798750211641949889184615;
    const Audio PI_A = 3.141592653589793238462643383279502884197169399375105820974944592307;
    
    const PreAudio ZERO_PA = 0.0;
    const PreAudio TAU_PA = 6.283185307179586476925286766559005768394338798750211641949889184615;
    const PreAudio PI_PA = 3.141592653589793238462643383279502884197169399375105820974944592307;
    
    const double PI_D = 3.141592653589793238462643383279502884197169399375105820974944592307;
    const float PI_F = 3.141592653589793238462643383279502884197169399375105820974944592307;
    const double TAU_D = 6.283185307179586476925286766559005768394338798750211641949889184615;
    const float TAU_F =  6.283185307179586476925286766559005768394338798750211641949889184615;
    
    constexpr double RECIP256_D = 1.0 / 256.0;
    constexpr float RECIP256_F = 1.f / 256.f;
    constexpr double RECIP1024_D = 1.0 / 1024.0;
    constexpr float RECIP1024_F = 1.f / 1024.f;

    
    ///  template inline functions: ============================================
    // Denormal Number Cancel ==================================================
    template<typename Fpn> inline Fpn DNC (Fpn inlet)      { if (!(inlet < -1.0e-8 || inlet > 1.0e-8)) inlet = 0; return inlet; }
    template<typename Fpn> inline void DNC_ref (Fpn& inlet) { if (!(inlet < -1.0e-8 || inlet > 1.0e-8)) inlet = 0;               }
    // clippers ===============================================================
    template<typename Fpn>inline Fpn clipMin    (Fpn inlet,  Fpn min = 0) { if (inlet < min) inlet = min; return inlet; }
    template<typename Fpn>inline void clipMin_ref(Fpn& inlet, Fpn min = 0) { if (inlet < min) inlet = min;               }
    template<typename Fpn>inline Fpn clipMax    (Fpn inlet,  Fpn max = 1) { if (inlet > max) inlet = max; return inlet; }
    template<typename Fpn>inline void clipMax_ref(Fpn& inlet, Fpn max = 1) { if (inlet > max) inlet = max;               }
    template<typename Fpn>inline Fpn clipMinMax    (Fpn inlet, Fpn min,Fpn max=1){if(inlet < min)inlet = min; else if(inlet > max)inlet = max; return inlet;}
    template<typename Fpn>inline void clipMinMax_ref(Fpn& inlet,Fpn min,Fpn max=1){if(inlet < min)inlet = min; else if(inlet > max)inlet = max;}
    // wrappers -  maintain a range with a modulo-like action ==================
    template<typename Fpn>inline Fpn wrapMax     (Fpn inlet, Fpn max)           { while (inlet > max) inlet -= max; return inlet;  }
    template<typename Fpn>inline void wrapMax_ref (Fpn& inlet, Fpn max)          { while (inlet > max) inlet -= max;                }
    template<typename Fpn>inline Fpn wrapMax     (Fpn  inlet,Fpn max,Fpn size) { while (inlet > max) inlet -= size; return inlet; }
    template<typename Fpn>inline void wrapMax_ref (Fpn& inlet,Fpn max,Fpn size) { while (inlet > max) inlet -= size;               }
    template<typename Fpn>inline Fpn wrapMin     (Fpn inlet,Fpn size,Fpn min=0){ while (inlet < min) inlet += size; return inlet; }
    template<typename Fpn>inline void wrapMin_ref(Fpn& inlet,Fpn size,Fpn min=0){ while (inlet < min) inlet += size;               }
    // saturators  ============================================================
    template<typename Fpn> inline Fpn hyperbolSat     (Fpn inlet, Fpn L)
    {   if (inlet >= 0) { inlet =  L - ( ( L / (L + abs(inlet)) ) * L ); }
         else         { inlet =  -(L - ( ( L / (L + abs(inlet)) ) * L )); } return inlet;
    }
    template<typename Fpn> inline void hyperbolSat_ref (Fpn& inlet, Fpn L)
    {   if (inlet >= 0) { inlet =  L - ( ( L / (L + abs(inlet)) ) * L ); }
         else         { inlet =  -(L - ( ( L / (L + abs(inlet)) ) * L )); }
    }                                                                               //    add template<typename T> class polySat31
    // shapers usually used on control signals ====================================
    template<typename Fpn> inline Fpn CltrShaper (Fpn inlet, Fpn one, Fpn half, Fpn zero)
    {   if (inlet >= 0.0) { inlet = (one - half) * 2.0 * (inlet - 0.5) + half; }
         else             { inlet = (half - zero) * 2.0 * inlet + zero; } return inlet;
    }
    template<typename Fpn> inline Fpn CltrShaper_ref (Fpn& inlet, Fpn one, Fpn half, Fpn zero)
    {   if (inlet >= 0.0) { inlet = (one - half) * 2.0 * (inlet - 0.5) + half; }
         else             { inlet = (half - zero) * 2.0 * inlet + zero; }
    }
    template<typename Fpn> inline Fpn dB2AF    (Fpn inlet) { inlet = pow(1.12202, inlet); return inlet; }
    template<typename Fpn> inline void dB2AF_ref(Fpn& inlet){ inlet = pow(1.12202, inlet);               }
    template<typename Fpn> inline Fpn xFade (Fpn x, Fpn in0, Fpn in1) { return ( (1 - x) * in0 ) + (x * in1); }
    //== interpolation =================================================
    template<typename Fpn> inline Fpn interpolate4 (Fpn index, Fpn iMinus1Sample, Fpn iSample, Fpn iPlus1Sample, Fpn iPlus2Sample )
    {   Fpn var1 = (iPlus1Sample - iMinus1Sample) * 0.5;
        Fpn var2 = iSample - iPlus1Sample;
        Fpn var3 = var1 + var2;
        Fpn var4 = var3 + ((iPlus2Sample - iSample) * 0.5);
        Fpn var5 = var4 + var2;
        Fpn var6 = ((index * var5) - var3 - var5) * index;
        return (var6 + var1) * index + iSample;
    }
    //== taking PhaseUni (0...1) input ==================================
    template<typename Fpn> inline Fpn sine4 (Fpn phase)
    {   float absPh = fabs(phase);
        return (phase * 68.5949) * (absPh + 0.232963) *
        (absPh - 0.5)  * (absPh - 0.732963);
    }
    template<typename Fpn> inline Fpn sine8 (Fpn phase)
    {   double absPh = fabs(phase);
        return phase *  60.2522 * ((absPh * (absPh + 1.05802)) + 0.436501) *
        (absPh + 0.424933) * ((absPh * (absPh - 2.05802)) + 1.21551) *
        (absPh - 0.5) * (absPh - 0.924933);
    }
    template<typename Fpn> inline Fpn wrap1 (Fpn phase)
    {   while (phase >= 1.0) phase -= 1.0;
        while (phase < 0.0) phase += 1.0;
        return phase;
    }

    template<typename Fpn> inline Fpn ratio1(Fpn phase,Fpn ratio) { return wrapMax((phase * ratio), 1.0); }
    template<typename Fpn> inline void ratio1_ref(Fpn phase,Fpn ratio){ wrapMax_ref((phase *= ratio), 1.0); }
    template<typename Fpn> inline Fpn phaseDistort (Fpn phase, Fpn knee)
    {   if (phase < knee) return (1 / knee) * phase * 0.5f;
        else return ( (1 / (1 - knee)) * (phase - knee) * 0.5f ) + 0.5f;
    }
    template<typename Fpn> inline void phaseDistort_ref (Fpn& phase, Fpn knee)
    {   if (phase < knee) phase = (1 / knee) * phase * 0.5f;
        else phase = ( (1 / (1 - knee)) * (phase - knee) * 0.5f ) + 0.5f;
    }
    ///  true trig functions: ==============================================
    template<typename Fpn> inline Fpn tanh (Fpn x)
    {   Fpn temp = pow(7.38906, x);
        return (-1 + temp) / (1 + temp);
    }

    ///  template classes: =================================================
    //-- Slew --------------------------------------------------------------
    template <class Fpn> class Slew
    { public:
        Slew (Fpn init, Fpn adder = 0.001, Fpn subt = 0.001)
        : add(adder),sub(subt), internal(init), prevIn(init), output(init){}
        
        void reset (Fpn init) { output = prevIn = internal = init; }
        
        void set (Fpn adder, Fpn subt) { add = adder; sub = subt; }
        
        Fpn operator()(Fpn input)
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
        void calc (Fpn input)
        {   diff = input - internal;  // want to find difference and
            if (diff > 0) { goUp = true; }  // determine direction.
        }
        void process(Fpn input)
        {   if (goUp)   // process rising output
            {   if (internal < input) { output = internal = internal + add; }
                else { output = internal = input; } // went too far. set to goal.
            }else       // process falling output
            {   if (internal > input) { output = internal = internal - sub; }
                else { output = internal = input; } // went too far. set to goal.
            }
        }
        Fpn add, sub, diff, internal; bool goUp;
    protected:
        Fpn prevIn, output, input;
    };
    
    
    //-- SlewLimiter -----------------------------------------------------------
    template <class Fpn> class SlewLimiter : public Slew<Fpn>
    { public:
        SlewLimiter (Fpn sRate, Fpn initValue = 0.f) : Slew<Fpn>(initValue)
        { msPerSample = 1000 / sRate; }
        void setSRate (Fpn sRate) { msPerSample = 1000 / sRate; }
        void set (Fpn upMsPer1, Fpn dnMsPer1)
        {   this->addsub (upMsPer1, dnMsPer1); }
    protected:
        void addsub(Fpn upMsPer1, Fpn dnMsPer1)
        {   Slew<Fpn>::add = msPerSample / upMsPer1;
            Slew<Fpn>::sub = msPerSample / dnMsPer1;
        }
        Fpn msPerSample;
    };
    //-- LinearRamp -----------------------------------------------------------
    template <class Fpn> class LinearRamp : public SlewLimiter<Fpn>
    { public:
        LinearRamp (Fpn sRate, Fpn initValue) : SlewLimiter<Fpn>(sRate,initValue)
        {}
        void set (Fpn upMs, Fpn dnMs) { this->upMs = upMs; this->dnMs = dnMs; }
        void calc (Fpn input)
        {   diff = input - Slew<Fpn>::internal;
            if (diff > 0) { Slew<Fpn>::goUp = true; }
            Slew<Fpn>::add =       diff  * SlewLimiter<Fpn>::msPerSample / upMs;
            Slew<Fpn>::sub = fabsf(diff) * SlewLimiter<Fpn>::msPerSample / dnMs;
        }
    private:
        Fpn upMs, dnMs, diff;
    };
    //-- PeakDetector -----------------------------------------------------------
    template <class Fpn> class PeakDetector : public SlewLimiter<Fpn>
    { public:
        PeakDetector<Fpn> (Fpn sRate) : SlewLimiter<Fpn>(sRate, 0.0)
        {   SlewLimiter<Fpn>::set (0.6f, 50); }
        Fpn operator()(Fpn input) {return SlewLimiter<Fpn>::operator() (fabs(input));}
    };
    //    class NonlinearRamp : public Slew
    
    
} // end namespace jATK
#endif  // INLINE_H_INCLUDED


