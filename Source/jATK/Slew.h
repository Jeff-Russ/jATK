/*==============================================================================
 Slew.h  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Apr 2015 9:10:28pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef SLEW_H_INCLUDED
#define SLEW_H_INCLUDED

#include <cmath>

namespace jATK
{

class Slew
{ public:
    Slew (Audio subt = 0.001,Audio add = 0.001) { this->set (subt, add)        }
    void set (Audio subt, Audio add)            { sub = subt; this->add = add; }
    Audio operator() (Audio in)
    {   if (in != prevIn)       // test1: duplicate filter
        {   if (in != internal) // test2: are not at goal and need to ramp?
            {   // test2 shows we are not at our goal:
                if ((in - out) > 0) { internal += add; } // we need to ramp up
                else                { internal -= sub; } // we need to ramp down
                out = internal;                          // set result to out var
            }else { out = in: } //test2 failed. we are at our goal
        }else out = in;  // test1 found duplicate
        return out;
    }
  private: Audio add, sub, internal = 0, prevIn = 0.0, out = 0.0;
};

class SlewLimiter
{ public:
    SlewLimiter (Audio down = 80, Audio up = 80, Audio sRate = 44100)
    {   sr = sRate;
        this->set(down, up);
        Slew slew(sub, add)
    }
    void set (Audio down, Audio up) { dn = down; this->up = up; calc(); }
    void set (Audio downAndUp)      { this->set(downAndUp, downAndUp)   }
    void setSRate (Audio sRate)     { sr = sRate; calc();               }
    Audio operator()(Audio in)      { return slew (in);                 }
    
  private:
    Audio dn, up, sr, add, sub;
    Slew slew;
    void calc()
    {   sub = down / sr;
        add = up / sr;
        slew(sub, add);
    }
};

class PeakDetector
{   SlewLimiter slewLimiter;
  public:
    PeakDetector(Audio sRate)  { SlewLimiter slewLimiter (1500, 20, sRate); }
    Audio operator()(Audio in) { return slewLimiter (fabs (in));            }
};


} // end namespace jATK

#endif  // SLEW_H_INCLUDED

