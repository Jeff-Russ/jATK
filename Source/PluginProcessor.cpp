/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JAtkAudioProcessor::JAtkAudioProcessor()
{
	UserParams[MasterBypass]=0.0f;//default to not bypassed
	UserParams[StereoWidth]=1.0f;//default Width 1.0 (no change)
	UIUpdateFlag=true;//Request UI update
}

JAtkAudioProcessor::~JAtkAudioProcessor()
{
}

//==============================================================================
const String JAtkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int JAtkAudioProcessor::getNumParameters()
{
    return totalNumParam;
}

float JAtkAudioProcessor::getParameter (int index)
{
	switch(index)
	{
		case MasterBypass://example nothing special
			return UserParams[MasterBypass];
		case StereoWidth://example update from internal
			return UserParams[StereoWidth];
		default: return 0.0f;//invalid index
	}
}

void JAtkAudioProcessor::setParameter (int index, float newValue)
{
	switch(index) 
	{
	case MasterBypass:
		UserParams[MasterBypass]=newValue;
		break; 
	case StereoWidth:
		UserParams[StereoWidth]=newValue;
		break;
	default: return;
	}
    UIUpdateFlag=true;//Request UI update in case this was called by host directly
}

const String JAtkAudioProcessor::getParameterName (int index)
{
	switch(index)
	{
	case MasterBypass: return "Master Bypass"; 
	case StereoWidth: return "StereoWidth Factor";
	default:return String::empty;
	}
}

const String JAtkAudioProcessor::getParameterText (int index)
{
	if(index>=0 && index<totalNumParam)
		return String(UserParams[index]);//return parameter value as string
	else return String::empty;
}

const String JAtkAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String JAtkAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool JAtkAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool JAtkAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool JAtkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JAtkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JAtkAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double JAtkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JAtkAudioProcessor::getNumPrograms()
{
    return 0;
}

int JAtkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JAtkAudioProcessor::setCurrentProgram (int index)
{
}

const String JAtkAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void JAtkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JAtkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JAtkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JAtkAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if(getNumInputChannels()<2 || UserParams[MasterBypass])
	{}/*Nothing to do here - processing is in-place, so doing nothing is pass-through (for NumInputs=NumOutputs)*/  
	else
	{//Not bypassed - do processing!
		float* leftData = buffer.getWritePointer(0);
		float* rightData = buffer.getWritePointer(1);
	}
}

//==============================================================================
bool JAtkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JAtkAudioProcessor::createEditor()
{
    return new JAtkAudioProcessorEditor (this);
}

//==============================================================================
void JAtkAudioProcessor::getStateInformation (MemoryBlock& destData)
{//Save UserParams/Data to file
	XmlElement root("Root");
	XmlElement *el;
	el = root.createNewChildElement("Bypass"); 
	el->addTextElement(String(UserParams[MasterBypass]));
	el = root.createNewChildElement("StereoWidth");
	el->addTextElement(String(UserParams[StereoWidth]));
	copyXmlToBinary(root,destData);
}

void JAtkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{//Load UserParams/Data from file
	XmlElement* pRoot = getXmlFromBinary(data,sizeInBytes);
	if(pRoot!=NULL)
	{
		forEachXmlChildElement((*pRoot),pChild)
		{
			if(pChild->hasTagName("Bypass"))
			{
				String text = pChild->getAllSubText();
				setParameter(MasterBypass,text.getFloatValue());
			}
			else if(pChild->hasTagName("StereoWidth"))
			{
				String text = pChild->getAllSubText();
				setParameter(StereoWidth,text.getFloatValue());
			} 
		}
		delete pRoot;
		UIUpdateFlag=true;//Request UI update
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JAtkAudioProcessor();
}
