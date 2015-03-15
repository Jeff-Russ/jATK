/*==============================================================================
 CAArray.cpp  :   Jeff's (Juce) Audio ToolKit
 Created: 15 Mar 2015 11:46:40am
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#include "CAArray.h"

namespace jATK
{   ///=== CAArray class implementation ========================================
    
    CAArray::CAArray()                { this->setSize(44100);      }
    CAArray::CAArray (int bufferSize) { this->setSize(bufferSize); }
    CAArray::~CAArray()               { this->deleteBuffer();      }
    void CAArray::deleteBuffer()      { delete[] array;            }
    int  CAArray::getSize()           { return bufSize;            }
    void CAArray::setSize (int bufferSize)
    {   bufSize = bufferSize;
        bufSizeFlt = (audio)bufSize;
        bufN = bufSize - 1;
        maxIntrDly = (audio)(bufN - 2);
        array = new audio [bufSize];
        this->clear();
    }
    void CAArray::clear()
    {   for (int i = 0; i < bufSize; i++) array[i] = 0.0;
        writeIdx = 0;
    }
    void CAArray::writeRT (audio sample)
    {   if (writeIdx < bufN) { writeIdx++; }
        else { writeIdx = 0; }
        array [writeIdx] = sample;
    }
    audio CAArray::getDelaySample (int offSet)
    {   // Check bounds:
        if (offSet <= bufSize && offSet >= 0)
        /*  everything was fine  */{ /* do nothing */  }
        else if (offSet > bufSize) { offSet = bufSize; }
        else /* offSet was neg. */ { offSet = -offSet; }
        
        // return sample:
        return array [wrapMin (writeIdx - offSet, bufN)];
    }
    audio CAArray::getSample (int index)
    {   if (index < bufSize && index >= 0) { return array [index]; }
        else if (index > bufN)             { return array[bufN];   }
        else                               { return array[0];      }
        
    }
    audio CAArray::getDelaySample4x (audio offSet)
    {   // check bounds:
        if (offSet <= maxIntrDly && offSet >= 0)
        /*  everything was fine  */{ /* do nothing */  }
        else if (offSet > maxIntrDly) { offSet = maxIntrDly; }
        else /* offSet was neg. */ { offSet = -offSet; }
        
        // define corrected offset as integer + fractional:
        dlyInteger = (int)offSet;
        dlyFractional = offSet - (audio)dlyInteger;
        
        // get offset for each interpolated line:
        idxMin1Offs = (clipMin (dlyInteger - 1));
        idxPlus0Offs = dlyInteger;
        idxPlus1Offs = dlyInteger + 1;
        idxPlus2Offs = dlyInteger + 2;
        
        // get indexes from those offsets:
        idxMin1  = wrapMin (writeIdx - idxMin1Offs,  bufSize);
        idxPlus0 = wrapMin (writeIdx - idxPlus0Offs, bufSize);
        idxPlus1 = wrapMin (writeIdx - idxPlus1Offs, bufSize);
        idxPlus2 = wrapMin (writeIdx - idxPlus2Offs, bufSize);
        
        return Interp4_AudioArr (dlyFractional, array[idxMin1],
                                                array[idxPlus0],
                                                array[idxPlus1],
                                                array[idxPlus2]);
    };
    audio CAArray::getSample4x (audio index) // this still has out of bounds
    {                                        // issues.
        // define corrected offset as integer + fractional:
        readInteger = (int)index;
        readFractional = index - (audio)readInteger;
        
        // get indexes from those offsets:
        idxMin1  = wrapMin (readInteger - 1,  bufSize);
        idxPlus0 = wrapMin (readInteger,      bufSize);
        idxPlus1 = wrapMin (readInteger + 1,  bufSize);
        idxPlus2 = wrapMin (readInteger + 2,  bufSize);
        
        return Interp4_AudioArr (readFractional, array[idxMin1],
                                 array[idxPlus0],
                                 array[idxPlus1],
                                 array[idxPlus2]);
    };
    ///=== END CAArray class implementation ====================================
} // end namespace jATK