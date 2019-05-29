/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A2_dromgoolAudioProcessorEditor::A2_dromgoolAudioProcessorEditor (A2_dromgoolAudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{
    
    // Make sure that before the constructor has finished, you've set the editor's size to whatever you need it to be.
    // Set up what main window can and cannot do.
    
    headerHeight = 90;
    LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Courier New");
    
    setOpaque(true);
    setSize (300, 450);
    setResizeLimits(300, 450, 400, 600);
    setResizable(true, true);
    
    
    // Images
    
    bgImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    
    
    // Ringmod slider
    
    freqLabel.setFont(Font (20.0f, Font::bold));
    freqLabel.setText("MODDER", dontSendNotification);
    freqLabel.setJustificationType(Justification::centred);
    freqLabel.attachToComponent(&freqSlider, false);
    freqSlider.setColour(Slider::ColourIds::trackColourId, Colours::darkred);
    freqSlider.setColour(Slider::ColourIds::backgroundColourId, Colours::darkgrey);
    freqSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    freqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    freqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    freqSlider.setRange(0.0f, 9000.0f);
    freqSlider.addListener(this);
    addAndMakeVisible(freqSlider);
    addAndMakeVisible(freqLabel);
    freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "freq", freqSlider));
    
    
    // Bitcrusher slider
    
    bitLabel.setFont(Font (20.0f, Font::bold));
    bitLabel.setText("CRUSHER", dontSendNotification);
    bitLabel.setJustificationType(Justification::centred);
    bitLabel.attachToComponent(&bitSlider, false);
    bitSlider.setColour(Slider::ColourIds::trackColourId, Colours::darkred);
    bitSlider.setColour(Slider::ColourIds::backgroundColourId, Colours::darkgrey);
    bitSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    bitSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    bitSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0,0);
    bitSlider.setRange(1, 16);
    bitSlider.addListener(this);
    addAndMakeVisible(bitSlider);
    addAndMakeVisible(bitLabel);
    bitAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "bit", bitSlider));
    
    
    // Distortion slider
    
    distLabel.setFont(Font (20.0f, Font::bold));
    distLabel.setText("SQUASHER", dontSendNotification);
    distLabel.setJustificationType(Justification::centred);
    distLabel.attachToComponent(&distSlider, false);
    distSlider.setColour(Slider::ColourIds::trackColourId, Colours::darkred);
    distSlider.setColour(Slider::ColourIds::backgroundColourId, Colours::darkgrey);
    distSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    distSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    distSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    distSlider.setRange(0.1f, 1.0f);
    distSlider.addListener(this);
    addAndMakeVisible(distSlider);
    addAndMakeVisible(distLabel);
    distAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "dist", distSlider));
    
    // Wet/dry mix slider
    
    mixLabel.setFont(Font (20.0f, Font::bold));
    mixLabel.setText("FRANKER/DANKER", dontSendNotification);
    mixLabel.setJustificationType(Justification::centred);
    mixLabel.attachToComponent(&mixSlider, false);
    mixSlider.setColour(Slider::ColourIds::trackColourId, Colours::darkred);
    mixSlider.setColour(Slider::ColourIds::backgroundColourId, Colours::darkgrey);
    mixSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    mixSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mixSlider.setRange(0.0f,1.0f);
    mixSlider.addListener(this);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(mixLabel);
    mixAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "mix", mixSlider));
   
}

A2_dromgoolAudioProcessorEditor::~A2_dromgoolAudioProcessorEditor()
{
}

//==============================================================================
void A2_dromgoolAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    
    // Add background image to plugin, make it fill up whole space and be resizeable
    
    g.drawImageWithin(bgImage, 0, 0, getWidth(), getHeight(), RectanglePlacement::fillDestination);
    
    g.setColour(Colours::white);
    g.setFont(Font("Courier New","monospace", 55.0f));
    g.drawFittedText("NOISIFIER", 0, 10, getWidth(), headerHeight, Justification::centredTop, 0);
    
}

void A2_dromgoolAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
    
    auto sliderHeight = (getHeight() - headerHeight) * 0.25f;
    auto padding = getWidth() * 0.05f;
    auto r = getLocalBounds();
    r.removeFromTop(headerHeight);
    auto controlOneSection = r.removeFromTop(sliderHeight);
    auto controlTwoSection = r.removeFromTop(sliderHeight);
    auto controlThreeSection = r.removeFromTop(sliderHeight);
    auto controlFourSection = r;
    
    freqSlider.setBounds(controlOneSection.reduced(padding));
    bitSlider.setBounds(controlTwoSection.reduced(padding));
    distSlider.setBounds(controlThreeSection.reduced(padding));
    mixSlider.setBounds(controlFourSection.reduced(padding));
    
}

void A2_dromgoolAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // use switch/case instead of if/else if there are a lot of these
    
    if (slider == &freqSlider)
    {
        processor.sinFreq = freqSlider.getValue();
    }
    else if (slider == &distSlider)
    {
        processor.distLevel = distSlider.getValue();
    }
    else if (slider == &bitSlider)
    {
        processor.bitLevel = bitSlider.getValue();
    }
    else if (slider == &mixSlider)
    {
        processor.mixLevel = mixSlider.getValue();
    }
}
