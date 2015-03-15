/*
  ==============================================================================

    Filters.h
    Created: 15 Mar 2015 2:28:10pm
    Author:  jefrus

  ==============================================================================
*/

#ifndef FILTERS_H_INCLUDED
#define FILTERS_H_INCLUDED

#include "helpers.h"

namespace jATK
{
    class StaticHP1
    { public:
        void setSampleRate (preAudio sampleRate);
        void setFrequency (preAudio frequency);
        audio filter (audio audioIn);
        audio filter (audio audioIn, preAudio frequency);
        
        
      private:
        preAudio frq, preAudio, sr, maxFq, minFq, PiSr;
        
    };

    
    
} // end namespace jATK

#endif  // FILTERS_H_INCLUDED
