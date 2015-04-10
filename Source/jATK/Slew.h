/*==============================================================================
 Slew.h  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Apr 2015 9:10:28pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef SLEW_H_INCLUDED
#define SLEW_H_INCLUDED

class Slew
{ public:
    Slew (Audio subt = 0.001,Audio add = 0.001) { this->set (subt, add)        }
    
    void set(Audio subt = 0.001, Audio add)     { sub = subt; this->add = add; }
    
    Audio operator()(Audio in)
    {   if (in != prevIn)       // test1: duplicate filter
        {   if (in != internal) // test2: are not at goal and need to ramp?
            {   // test2 shows we are not at our goal:
                if ((in - out) > 0) { internal += add; } // we need to ramp up
                else                { internal -= sub; } // we need to ramp down
                out = internal;                          // set result to out var
            }
            else { out = in: } //test2 failed. we are at our goal
        }
        else out = in;  // test1 found duplicate
        return out;
    }
private: Audio add, sub, internal = 0, prevIn = 0.0, out = 0.0;
};
#endif  // SLEW_H_INCLUDED
