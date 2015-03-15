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
        audio getDelaySample  (int offSet);
        audio getDelaySample4x  (audio offSet);
    private:
        int getIndexMin1();
        int getIndexPlus0();
        int getIndexPlus1();
        int getIndexPlus2();
        void deleteBuffer();
        audio* array;
        int bufSize, bufN, writeIdx, dlyInteger;
        
        int idxMin1Offs, idxPlus0Offs,idxPlus1Offs,
        idxPlus2Offs, idxMin1, idxPlus0, idxPlus1, idxPlus2, dlyIdx;
        
        audio bufSizeFlt, maxIntrDly, writeIdxFlt, dlyFractional, inMin1, inPlus0, inPlus1, inPlus2, output;
    };

    ///=========================================================================
} // end namespace jATK


#endif  // CAARRAY_H_INCLUDED
