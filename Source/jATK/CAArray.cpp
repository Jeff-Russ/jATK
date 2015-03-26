/*==============================================================================
 CAArray.cpp  :   Jeff's (Juce) Audio ToolKit
 Created: 15 Mar 2015 11:46:40am
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#include "CAArray.h"

namespace jATK
{
    ///=== CAArray class implementation ========================================
    CAArray::CAArray()                { this->setSize(44100);      }
    CAArray::CAArray (int bufferSize) { this->setSize(bufferSize); }
    CAArray::~CAArray()               { this->deleteBuffer();      }
    void CAArray::deleteBuffer()      { delete[] array;            }
    int  CAArray::getSize()           { return bufSize;            }
    void CAArray::setSize (int bufferSize)
    {   bufSize = bufferSize;
        bufSize_A = (Audio)bufSize;
        bufSizeFlt = bufSize_A;
        bufN = bufSize - 1;
        max4xDly = (Audio)(bufN - 2);
        array = new Audio [bufSize];
        this->clear();
    }
    void CAArray::clear()
    {   for (int i = 0; i < bufSize; i++) array[i] = 0.0;
        writeIdx = 0;
    }
    void CAArray::record (Audio sample)
    {   if (writeIdx < bufN) { writeIdx++;   }
         else                { writeIdx = 0; }
        array [writeIdx] = sample;
    }
    void  CAArray::write (Audio sample, int index)
    {   index = clipMinMax(index, 0, bufN);
        array [index] = sample;
    }
    Audio CAArray::getDelaySample (int offSet)
    {   // Check bounds:
        if (offSet <= bufSize && offSet >= 0)
        /*  everything was fine  */ { /* do nothing */  }
         else if (offSet > bufSize) { offSet = bufSize; }
         else /* offSet was neg. */ { offSet = -offSet; }
        
        // return sample:
        return array [wrapMin (writeIdx - offSet, bufN)];
    }
    Audio CAArray::getDelaySample (Audio offSet)
    {   // check bounds:
        if (offSet <= max2xDly && offSet >= 0)
        /*  everything was fine  */  { /* do nothing */  }
         else if (offSet > max2xDly) { offSet = max2xDly; }
         else /* offSet was neg. */  { offSet = -offSet; }
        
        // define corrected offset as integer + fractional:
        dlyInteger = (int)offSet;
        dlyFractional = offSet - (Audio)dlyInteger;
        
        // get offset for each pre-interpolated sample:
        idxPlus0Offs = dlyInteger;
        idxPlus1Offs = dlyInteger + 1;
        
        // get indexes from those offsets:
        idxPlus0 = wrapMin (writeIdx - idxPlus0Offs, bufSize);
        idxPlus1 = wrapMin (writeIdx - idxPlus1Offs, bufSize);
        
        return xFade(dlyFractional, array[idxPlus0], array[idxPlus1]);
    }
    Audio CAArray::getDelaySample4x (Audio offSet)
    {   // check bounds:
        if (offSet <= max4xDly && offSet >= 1)
        /*  everything was fine  */  { /* do nothing */   }
         else if (offSet > max4xDly) { offSet = max4xDly; }
         else if (offSet == 0)       { offSet = 1;        }
         else /* offSet was neg. */  { offSet = -offSet;  }
        
        // define corrected offset as integer + fractional:
        dlyInteger = (int)offSet;
        dlyFractional = offSet - (Audio)dlyInteger;
        
        // get offset for each pre-interpolated sample:
        idxMin1Offs = (clipMin (dlyInteger - 1));
        idxPlus0Offs = dlyInteger;
        idxPlus1Offs = dlyInteger + 1;
        idxPlus2Offs = dlyInteger + 2;
        
        // get indexes from those offsets:
        idxMin1  = wrapMin (writeIdx - idxMin1Offs,  bufSize);
        idxPlus0 = wrapMin (writeIdx - idxPlus0Offs, bufSize);
        idxPlus1 = wrapMin (writeIdx - idxPlus1Offs, bufSize);
        idxPlus2 = wrapMin (writeIdx - idxPlus2Offs, bufSize);
        
        return interpolate4 (dlyFractional, array[idxMin1],
                                            array[idxPlus0],
                                            array[idxPlus1],
                                            array[idxPlus2]);
    };
    Audio CAArray::getSample (int index)
    {   if (index < bufSize && index >= 0) { return array [index]; }
         else if (index > bufN)            { return array[bufN];   }
         else                              { return array[0];      }
        
    }
    Audio CAArray::getSample (Audio index)
    {   if (index < bufSize_A && index >= ZERO_A)
        {  // define corrected offset as integer + fractional:
            readInteger = (int)index;
            readFractional = index - (Audio)readInteger;
            
            // get indexes from those offsets:
            idxPlus0 = wrapMin (readInteger,     bufSize);
            idxPlus1 = wrapMin (readInteger + 1, bufSize);
            
            return xFade(readFractional, array[idxPlus0], array[idxPlus1]);
        } else return 0.0;
    }
    Audio CAArray::getSample4x (Audio index) 
    {   if (index < bufSize_A && index >= ZERO_A)
        {   // define corrected offset as integer + fractional:
            readInteger = (int)index;
            readFractional = index - (Audio)readInteger;
            
            // get indexes from those offsets:
            idxMin1  = wrapMin (readInteger - 1, bufSize);
            idxPlus0 = wrapMin (readInteger,     bufSize);
            idxPlus1 = wrapMin (readInteger + 1, bufSize);
            idxPlus2 = wrapMin (readInteger + 2, bufSize);
            
            return interpolate4 (readFractional, array[idxMin1],
                                     array[idxPlus0],
                                     array[idxPlus1],
                                     array[idxPlus2]);
        } else return 0.0;
    };
    ///=== END CAArray class implementation ====================================
} // end namespace jATK