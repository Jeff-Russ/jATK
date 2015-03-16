/*==============================================================================
 CAArray.h  :   Jeff's (Juce) Audio ToolKit
 Created: 15 Mar 2015 11:46:40am
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef CAARRAY_H_INCLUDED
#define CAARRAY_H_INCLUDED

#include "helpers.h"

namespace jATK

{   ///=========================================================================
    class CAArray
    {  public:
        CAArray();                  // default will set size to 44100
        CAArray (int bufferSize);   // set # of samples in array and clear
        ~CAArray();
        int  getSize();                 // remind yourself of it's size
        void setSize (int bufferSize);  // set # of samples in array and CLEAR!
        void clear();                   // set all samples to zero
        void  record (Audio sample);    // self incrementing way of filling array
        void  write (Audio sample, int index); // non-self-incr, by-index way
        Audio getDelaySample  (int offSet);    // arg is subracted from current 
        Audio getDelaySample  (Audio offSet);  // same but with 2x interpolation
        Audio getDelaySample4x  (Audio offSet);// same but with 4x interpolation
        Audio getSample (int index);           // get sample directly but index
        Audio getSample (Audio index);         // same but with 2x interpolation
        Audio getSample4x (Audio index);       // same but with 4x interpolation
    private: // stuff that doesn't concern you:
        int getIndexMin1();     // just some varibles that
        int getIndexPlus0();    // are used internally
        int getIndexPlus1();    // by the interpolation
        int getIndexPlus2();    // methods.
        void deleteBuffer();    // Frees allocated memory!
        Audio* array;           // The actual array!
        int bufSize, bufN, writeIdx, dlyInteger, readInteger;
        
        int idxMin1Offs, idxPlus0Offs,idxPlus1Offs, idxPlus2Offs,
            idxMin1,     idxPlus0,    idxPlus1,     idxPlus2;
        
        Audio bufSizeFlt, max2xDly, max4xDly, writeIdxFlt,
                dlyFractional, readFractional;
    };
    ///=========================================================================
} // end namespace jATK


#endif  // CAARRAY_H_INCLUDED
