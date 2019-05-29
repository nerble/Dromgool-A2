/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class A2_dromgoolAudioProcessorEditor  : public AudioProcessorEditor, Slider::Listener
{
public:
    A2_dromgoolAudioProcessorEditor (A2_dromgoolAudioProcessor&, AudioProcessorValueTreeState&);
    ~A2_dromgoolAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    // Background image
    
    Image bgImage;
    
    //
    // Height of canvas for title of plugin
    //
    
    int headerHeight;
    
    Slider mixSlider;
    Label mixLabel;
    
    Slider freqSlider;
    Label freqLabel;
    
    Slider bitSlider;
    Label bitLabel;
    
    Slider distSlider;
    Label distLabel;
    
    
    // Creating attachments to connect sliders to the APVTS (audio processor)
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freqAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bitAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> distAttachment;
    
    ImageButton bypassButton; // create button object
    
    void sliderValueChanged(Slider* slider) override; // need to override predeclared virtual function to use it
    AudioProcessorValueTreeState& valueTreeState; // ampersand says it is a reference point/ID/link
    A2_dromgoolAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A2_dromgoolAudioProcessorEditor)
};
