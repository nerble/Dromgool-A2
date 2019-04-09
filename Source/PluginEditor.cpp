/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A2_dromgoolAudioProcessorEditor::A2_dromgoolAudioProcessorEditor (A2_dromgoolAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    // set up what main window can and cannot do
    setOpaque(true);
    // setSize (600, 400);
    setResizeLimits(450, 300, 600, 400);
    setResizable(true, true);
    
    mixLabel.setText("Wet/Dry Mix", dontSendNotification);
    mixLabel.setJustificationType(Justification::centred);
    mixLabel.attachToComponent(&mixSlider, false);
    mixSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::red);
    mixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 80, mixSlider.getTextBoxHeight());
    
    // set ranges from 0 to 1 ideally, as floats.  Best for implementation
    mixSlider.setRange(0.0f,1.0f);
    mixSlider.setNumDecimalPlacesToDisplay(2);
    
    mixSlider.setTextValueSuffix(" %");
    mixSlider.addListener(this);
    mixSlider.setValue(0.5f);
    
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(mixLabel);
    
    
    freqLabel.setText("Frequency", dontSendNotification);
    freqLabel.setJustificationType(Justification::centred);
    freqLabel.attachToComponent(&freqSlider, false);
    freqSlider.setColour(Slider::ColourIds::trackColourId, Colours::red);
    freqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    freqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 120, freqSlider.getTextBoxHeight());
    
    freqSlider.setRange(300.0f, 9000.0f);
    freqSlider.setNumDecimalPlacesToDisplay(0);
    freqSlider.setTextValueSuffix(" Hz");
    freqSlider.addListener(this);
    freqSlider.setValue(300.0f);
    //freqSlider.setSkewFactorFromMidPoint(1000);
    
    addAndMakeVisible(freqSlider);
    addAndMakeVisible(freqLabel);
   
}

A2_dromgoolAudioProcessorEditor::~A2_dromgoolAudioProcessorEditor()
{
}

//==============================================================================
void A2_dromgoolAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // set up look and feel (theme)
    //g.fillAll (getLookAndFeel().findColour
    //           (ResizableWindow::backgroundColourId));
    g.fillAll(Colours::black);
    // g.setColour (Colours::white);
    // g.setFont(12.0f);
    // g.drawFittedText ("VSTs ARE AMAZING.", getLocalBounds(),
    //                   Justification::centred, 1);
    
    g.setColour(Colours::white);
    g.setFont(Font("Arial",20.0f,Font::bold));
    g.drawFittedText("RING MODULATOR", 0, 5, getWidth(), 50, Justification::centred, 5);
    
    // g.setColour(Colours::red); // set color of stroke/outline
    // first two are where on the plugin
    
    //g.drawRect(getWidth(), getHeight(), getWidth(), getHeight(), 1); // last arg == stroke width (optional)
    //g.fillRect(getWidth(), getHeight(), getWidth(), getHeight());
    
    //g.setColour(Colours::hotpink);
    // g.drawLine(5.0f, 5.0f, getWidth(), getHeight()); // use get width etc to keep it relative
    
    // g.drawEllipse(50, 100, getWidth()/2, getHeight()/2, 5);
    
    // a slider is anything that is continuous and moves
    
    
    
    
}

void A2_dromgoolAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // lay out subcomponents here, so when VST is resized stuff will get moved automatically
    //mixSlider.setBounds(50, getHeight()-120, getWidth()/3, 100);
    mixSlider.setBounds(getWidth()/9, getHeight()/4, getWidth()/3, getHeight()/2);
    
    freqSlider.setBounds((getWidth()/7)*4, getHeight()/4, getWidth()/3, getHeight()/2);
}

void A2_dromgoolAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // use switch/case instead of if/else if there are a lot of these
    
    // need to dereference the memory address of mixSlider
    if (slider == &mixSlider)
    {
        // get the vaue on current slider, pass value to audio processor
        // processor is our class name declared bottom of PluginEditor.h
        processor.mixLevel.setTargetValue(mixSlider.getValue());
        //processor.mixLevel = mixSlider.getValue();
        
        // do something here like set gain?
        // bad way to do this because you made a private variable public  in PluginProcessor
        // rather than use getter/setter function
        //processor.gain.setGainLinear(mixSlider.getValue());
    } else if (slider == &freqSlider)
    {
        // need to figure out how to updateAngleDelta
        processor.sinFreq = freqSlider.getValue();
        // do something here like set gain
        // bad way to do this because you made a private variable public  in PluginProcessor
        // rather than use getter/setter function
        //processor.gain.setGainLinear(freqSlider.getValue());
    }
}
