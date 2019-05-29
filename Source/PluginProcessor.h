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
    
    // State information routines
    
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    // Ring modulator defs
    
    float sinFreq; // frequency of sine wave we are trying to create
    float sinFreqLast;
    void updateAngleDelta();
    
    
    // For "squasher" distortion
    
    float distLevel;
    
    
    // For bitcrusher
    
    int bitLevel;
    
    // for mixer
    
    float mixLevel;
    
private:
    
    // Ring modulator
    
    float currentSampleRate;
    float currentAngle;
    float angleDelta;
    
    
    // Automation

    float* mixParameter     = nullptr;
    float* freqParameter    = nullptr;
    float* bitParameter     = nullptr;
    float* distParameter    = nullptr;
    float* bypassParameter  = nullptr;
    
    
    // State
    
    AudioProcessorValueTreeState parameters;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A2_dromgoolAudioProcessor)
};
