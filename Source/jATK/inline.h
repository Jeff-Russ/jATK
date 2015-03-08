/*
  ==============================================================================

    inline.h
    Created: 8 Mar 2015 2:22:45pm
    Author:  Jeff-Russ

  ==============================================================================
*/

#ifndef INLINE_H_INCLUDED
#define INLINE_H_INCLUDED

#include "types.h"

namespace jATK
{
    ///=========================================================================
    
inline audio clip0 (audio inlet)
{   if (inlet >= 0.0) { return inlet;}
    else              { return 0.0;  }
}


} // end namespace jATK





#endif  // INLINE_H_INCLUDED
