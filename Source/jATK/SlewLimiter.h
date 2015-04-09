/*==============================================================================
 SlewLimiter.h  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Apr 2015 9:10:28pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef SLEWLIMITER_H_INCLUDED
#define SLEWLIMITER_H_INCLUDED

class SlewLimiter
{ public:
    SlewLimiter (Audio down = 80, Audio up = 80, Audio sRate = 44100.0 )
    { this->set (down, up, sRate) }
    void set(Audio down, Audio up, Audio sRate)
    {   sr = sRate;
        this->set (down, up);
    }
    void set(Audio downAndUp) { this->set (downAndUp, downAndUp); }
    void set(Audio down, Audio up)
    {   dn = down; this->up = up;
        add = up / sr;
        sub = dn / sr;
    }
    
    Audio operator=()(Audio in)
    {   if (in != prevIn)
    {   if (in == internal) out = in
        else
        {   if ( (in - out) > 0 ) // we need to incr.
        {   if (internal < in)
            
            }
        else                  // we need to decr.
        {
            
        }
            
        }
        
    }
    else out = in;
        
        return out;
        
    }
private:
    
    Audio dn, up, sr, add, sub, internal = 0, prevIn = 0.0, out = 0.0;
};




#endif  // SLEWLIMITER_H_INCLUDED
