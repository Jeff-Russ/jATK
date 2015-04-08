/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_binary_data_0[] =
"# Jeff's (Juce) Audio ToolKit\r\n"
"\r\n"
"### About: ###\r\n"
"* jATK provides a library of classes useful for audio effect and synthesizers, available via the jATK namespace\r\n"
"* All classes must be compatable with the Juce C++ framework and SHOULD be portable to other frameworks\r\n"
"* The entire ToolKits must be free of any restrictive licences.\r\n"
"* The focus of the ToolKit is mainly on duplicating the modules found in graphical audio programming environments such as Pure Data, Reaktor, Reaktor Core, and Max/MSP and creating new ones in a more professional and efficent C++ environment.\r\n"
"\r\n"
"### Status: ###\r\n"
"* This project is just beginning. It's not in a workable state yet but rather just a dumping ground.\r\n"
"* Anyone who wishes to add to it can push their code. I'll strip my name of the the title if other contribute a lot! \r\n"
"\r\n"
"### Goals: ###\r\n"
"1) Both math and table based sine oscilators that are capable of phase modululation, phase distortion, FM and additive networks... with very low CPU use\r\n"
"\r\n"
"2) Math based analog-style oscillators with anti-aliasing, using the same phasors used by the sine generators\r\n"
"\r\n"
"3) Envelopes, LFOs and LSDJ-style tables\r\n"
"\r\n"
"4) High quality ZDF and biquad filters for synthesizers and effects\r\n"
"\r\n"
"5) Delay/AllPass-based functions for delay, chorus and reverb creation.\r\n"
"\r\n"
"   These will be based on the base class CAArray which is a circular audio array:\r\n"
"\r\n"
" \r\n"
"                             OscLUT---SineLUT---AdditiveSineLUT\r\n"
"    CAArray--|--LookupTable_/\r\n"
"             |              l_SamplerLUT\r\n"
"             |\r\n"
"             |--Delay---MultiTapDelay\r\n"
"             |\r\n"
"             \\-Interpolator   APFilter\r\n"
"              \\             /\r\n"
"               CALattice---|-DiffDelay\r\n"
"                            \\\r\n"
"                             CombFilter\r\n";

const char* README_md = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x64791dc8:  numBytes = 1773; return README_md;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "README_md"
};

}
