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
        CAArray();
        CAArray (int bufferSize);
        ~CAArray();
        int  getSize();
        void setSize (int bufferSize);
        void clear();
        void  writeRT (audio sample);
        void  write (audio sample, int index);
        audio getDelaySample  (int offSet);
        audio getDelaySample2x  (audio offSet);
        audio getDelaySample4x  (audio offSet);
        audio getSample (int index);
        audio getSample4x (audio index);
    private:
        int getIndexMin1();
        int getIndexPlus0();
        int getIndexPlus1();
        int getIndexPlus2();
        void deleteBuffer();
        audio* array;
        int bufSize, bufN, writeIdx, dlyInteger, readInteger;
        
        int idxMin1Offs, idxPlus0Offs,idxPlus1Offs, idxPlus2Offs,
            idxMin1,     idxPlus0,    idxPlus1,     idxPlus2;
        
        audio bufSizeFlt, max2xDly, max4xDly, writeIdxFlt,
                dlyFractional, readFractional;
    };

    ///=========================================================================
} // end namespace jATK


#endif  // CAARRAY_H_INCLUDED
