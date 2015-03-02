# Jeff's (Juce) Audio ToolKit

### About: ###
* jATK provides a library of classes useful for audio effect and synthesizers, available via the jATK namespace
* All classes must be compatable with the Juce C++ framework and SHOULD be portable to other frameworks
* The entire ToolKits must be free of any restrictive licences.
* The focus of the ToolKit is mainly on duplicating the modules found in graphical audio programming environments such as Pure Data, Reaktor, Reaktor Core, and Max/MSP and creating new ones in a more professional and efficent C++ environment.

### Status: ###
* This project is just beginning. It's not in a workable state yet but rather just a dumping ground.
* Anyone who wishes to add to it can push their code. I'll strip my name of the the title if other contribute a lot! 

### Goals: ###
1) Both math and table based sine oscilators that are capable of phase modululation, phase distortion, FM and additive networks... with very low CPU use
2) Math based analog-style oscillators with anti-aliasing, using the same phasors used by the sine generators
3) Envelopes, LFOs and LSDJ-style tables
4) High quality ZDF and biquad filters for synthesizers and effects
5) Delay/AllPass-based functions for delay, chorus and reverb creation.

