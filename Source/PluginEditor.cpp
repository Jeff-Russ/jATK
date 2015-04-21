/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
JAtkAudioProcessorEditor::JAtkAudioProcessorEditor (JAtkAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Stereo Width Factor:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::grey);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (WidthCtrlSld = new Slider ("Width Factor Slider"));
    WidthCtrlSld->setRange (0, 5, 0.1);
    WidthCtrlSld->setSliderStyle (Slider::LinearHorizontal);
    WidthCtrlSld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    WidthCtrlSld->addListener (this);

    addAndMakeVisible (BypassBtn = new TextButton ("Bypass Button"));
    BypassBtn->setButtonText (TRANS("Bypass"));
    BypassBtn->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 125);


    //[Constructor] You can add your own custom stuff here..
	getProcessor()->RequestUIUpdate();//UI Update must be done each time a new editor is constructed
	startTimer(200);//starts timer with interval of 200mS
	BypassBtn->setClickingTogglesState(true);
    //[/Constructor]
}

JAtkAudioProcessorEditor::~JAtkAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    WidthCtrlSld = nullptr;
    BypassBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void JAtkAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JAtkAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (16, 16, 150, 24);
    WidthCtrlSld->setBounds (24, 40, 360, 24);
    BypassBtn->setBounds (24, 72, 360, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JAtkAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	JAtkAudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == WidthCtrlSld)
    {
        //[UserSliderCode_WidthCtrlSld] -- add your slider handling code here..
		ourProcessor->setParameterNotifyingHost(JAtkAudioProcessor::StereoWidth, (float)WidthCtrlSld->getValue());
        //[/UserSliderCode_WidthCtrlSld]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void JAtkAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
	JAtkAudioProcessor* ourProcessor = getProcessor();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == BypassBtn)
    {
        //[UserButtonCode_BypassBtn] -- add your button handler code here..
		ourProcessor->setParameterNotifyingHost(JAtkAudioProcessor::MasterBypass, (float)BypassBtn->getToggleState());
        //[/UserButtonCode_BypassBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void JAtkAudioProcessorEditor::timerCallback()
{
	JAtkAudioProcessor* ourProcessor = getProcessor();
	//exchange any data you want between UI elements and the Plugin "ourProcessor"
	if(ourProcessor->NeedsUIUpdate())
	{
		BypassBtn->setToggleState(1.0f == ourProcessor->getParameter(JAtkAudioProcessor::MasterBypass), dontSendNotification);
		WidthCtrlSld->setValue(ourProcessor->getParameter(JAtkAudioProcessor::StereoWidth), dontSendNotification);
		ourProcessor->ClearUIUpdateFlag();
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JAtkAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="JAtkAudioProcessor* ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="400" initialHeight="125">
  <BACKGROUND backgroundColour="ff000000"/>
  <LABEL name="new label" id="1d55c1b6b2497503" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 16 150 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Stereo Width Factor:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="Width Factor Slider" id="3256f6e24cbd10aa" memberName="WidthCtrlSld"
          virtualName="" explicitFocusOrder="0" pos="24 40 360 24" min="0"
          max="5" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Bypass Button" id="c5ac589830caa3ec" memberName="BypassBtn"
              virtualName="" explicitFocusOrder="0" pos="24 72 360 24" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
