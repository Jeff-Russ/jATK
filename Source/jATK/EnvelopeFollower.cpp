/*==============================================================================
 EnvelopeFollower.h  :   Jeff's (Juce) Audio ToolKit
 Created: 10 Apr 2015 12:18:51pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef ENVELOPEFOLLOWER_H_INCLUDED
#define ENVELOPEFOLLOWER_H_INCLUDED

#include <cmath>
#include "helpers.h"

namespace jATK
{
    class EnvelopeFollower
    {  public:
        EnvelopeFollower (Audio sRate, Audio attInSeconds, Audio decInSeconds)
        {   sr = sRate; a = attInSeconds; d = decInSeconds;
            this->calc();
        }
        void setSRate (Audio sRate)
        {   sr = sRate;
            this->calc();
        }
        void set (Audio attInSeconds, Audio decInSeconds)
        {   a = attInSeconds; d = decInSeconds;
            this->calc();
        }
        Audio operator()(Audio inlet)
        {   inlet = prevOut - fabs(inlet);
            if (inlet > 0)
                return aMult * inlet;
            else return dMult * inlet;
        }
    private:
        void calc()
        {   aMult = (clipMin (a * sr, Audio(1)) / 0.693147);
            dMult = (clipMin (d * sr, Audio(1)) / 0.693147);
        }
        Audio sr, a, d, aMult, dMult, prevOut = 0;
        
    };
} // end namespace jATK
#endif  // ENVELOPEFOLLOWER_H_INCLUDED
