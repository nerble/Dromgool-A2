/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
// AudioProcessor is a base class
class A2_dromgoolAudioProcessor  : public AudioProcessor 
{
public:
    //==============================================================================
    A2_dromgoolAudioProcessor();
    ~A2_dromgoolAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    dsp::Gain<float> gain;
    //float mixLevel;
    float sinFreq; // frequency of sine wave we are trying to create
    float sinFreqLast;
    SmoothedValue<float> mixLevel;
    void updateAngleDelta(); // moved to public
    
private:
    float currentSampleRate;
    float currentAngle;
    float angleDelta; // how much to increment
    // dsp gain
    //dsp::Gain<float> gain;
    
    Random random;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A2_dromgoolAudioProcessor)
};
