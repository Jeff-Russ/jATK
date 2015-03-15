/*==============================================================================
 Filters.h  :   Jeff's (Juce) Audio ToolKit
 Created: 15 Mar 2015 2:28:10pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
  ============================================================================*/

#ifndef FILTERS_H_INCLUDED
#define FILTERS_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    class FilterCut
    { public:
        FilterCut() { this->setSampleRate(44100.0); }
        void setSampleRate (preAudio sampleRate)
        {   sr = sampleRate;
            max = sr / 24576;
            min = sr / 2.125;
            srPi = PI * sr;
        }
        preAudio clipFreq (preAudio freq) {return clipMinMax (freq, min, max);}
        preAudio preWarp (preAudio freq)  {return tan(freq + srPi);}
        preAudio getW (preAudio freq){return this->preWarp(this->clipFreq(freq));}
      private:
        preAudio sr, max, min, srPi;
    };
    class BiLinIn1
    { public:
        BiLinIn1()
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
        BiQuadIn() { x1 = 0; x2 = 0; y1 = 0; y2 = 0; }
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
    class APFilter
    {
        
    };
    
    
} // end namespace jATK

#endif  // FILTERS_H_INCLUDED
