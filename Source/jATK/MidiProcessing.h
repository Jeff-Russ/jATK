/*==============================================================================
 MidiProcessing.h  :   Jeff's (Juce) Audio ToolKit
 Created: 8 Apr 2015 7:04:08pm
 Author:  Jeff-Russ     https://github.com/Jeff-Russ
 =============================================================================*/

#ifndef MIDIPROCESSING_H_INCLUDED
#define MIDIPROCESSING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "helpers.h"

namespace jATK
{
    class MidiNoteProcessor
    { private:
        int outNote,sample_number, activeNote = -1;
        uint8 outVelo = 0;
        MidiMessage midi_message, midi_insert;
        void glide (int startNote, int endNote)
        {   // add slew limiter to pitch bend
        }
        void glide (int zero)
        {   // clean up when done
        }
    public:
        void MonolegatoGlide(MidiBuffer& midiMessages)
        {
            MidiBuffer::Iterator midi_buffer_iterator (midiMessages);
            while (midi_buffer_iterator.getNextEvent (midi_message,sample_number))
            {
                /*__________________ NOTE ON _________________________________*/
                if (midi_message.isNoteOn())
                {   int n = midi_message.getNoteNumber();
                    if (activeNote == -1)      // all is clear; new note w/gate
                        activeNote = n;        // set our flag
                    else if (n != activeNote){ // dissimilar note overlap (legato)
                        glide (activeNote, n); // process glide
                        midiMessages.clear (sample_number, 1); // block note
                        /* the receiving device will still thinks it's playing
                         activeNote so we have to make sure to kill it eventually*/
                    }
                    // else would mean two on's in a row of same pitch. let it pass?
                }
                /*__________________ NOTE OFF ________________________________*/
                else if (midi_message.isNoteOff())
                {   int n = midi_message.getNoteNumber();
                    if (n == activeNote){ // we were not in legato state. we can
                        activeNote = -1; // let note off pass and clear our flag
                        glide (0);       // tell glide we are done
                    }else /* we were in legato mode and this is an old note
                           that never made it's way out anyway. clear it.*/
                        midiMessages.clear (sample_number, 1); // it's irrelevant
                }
            }
        }
        
    };
    
    class MidiRate
    { public:
        MidiRate (Audio sRate, int bufferSize ) : sr(sRate), bSize(bufferSize)
        { mBufSize = 1000; this->calc(); }
        
        void setSRate      (Audio sRate)    { sr = sRate;        this->calc(); }
        void setBufferSize (int bufferSize) { bSize = bufferSize;this->calc(); }
        void setMidiRate   (int midiRate)   { mRate = midiRate;  this->calc(); }
        int operator() ( )                  { return mBufSize;                 }
        
    private:
        void calc() { mBufSize = mRate / sr * bSize; }
        Audio sr; int bSize, mRate, mBufSize;
    };
} // end namespace jATK
#endif  // MIDIPROCESSING_H_INCLUDED
