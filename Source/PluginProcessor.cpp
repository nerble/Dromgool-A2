/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>
#include <complex.h>



//==============================================================================
A2_dromgoolAudioProcessor::A2_dromgoolAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )

#endif
{
    // initialise some global variables
    
    currentSampleRate     = 0.0f;
    currentAngle          = 0.0f;
    angleDelta            = 0.0f;
    sinFreq               = 0.0f;

}

A2_dromgoolAudioProcessor::~A2_dromgoolAudioProcessor()
{
}

//==============================================================================
const String A2_dromgoolAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool A2_dromgoolAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool A2_dromgoolAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool A2_dromgoolAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double A2_dromgoolAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int A2_dromgoolAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int A2_dromgoolAudioProcessor::getCurrentProgram()
{
    return 0;
}

void A2_dromgoolAudioProcessor::setCurrentProgram (int index)
{
}

const String A2_dromgoolAudioProcessor::getProgramName (int index)
{
    return {};
}

void A2_dromgoolAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void A2_dromgoolAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Pre-playback initialisation
    currentSampleRate = sampleRate;
    sinFreq = 300.0f;
    updateAngleDelta();
    mixLevel.reset(currentSampleRate,0.02f); // second part is ramp up in seconds
    mixLevel.setTargetValue(0.9f);
    //mixLevel = 0.9f;
    
    //gain.setGainDecibels(0.0f);
    
    String message;
    message << "Preparing to play..." << newLine;
    message << "My sample rate is: " << currentSampleRate << newLine;
    message << "My sine wave frequency is " << sinFreq << "Hz" << newLine;
    message << "Audio buffer size is " << samplesPerBlock << newLine;
    Logger::getCurrentLogger()->writeToLog(message);

}

void A2_dromgoolAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool A2_dromgoolAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void A2_dromgoolAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    // Get total number of system input and output channels
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Made a copy of input buffer so we can change this while keeping our original
    AudioBuffer<float> wetBuffer(totalNumInputChannels, buffer.getNumSamples());
    wetBuffer.makeCopyOf(buffer);
    
    // Main audio processing loop
    // 1. Go through each audio input channel that is available (usually 2 for stereo)
    // 2. Modulate copied samples in wet buffer using our generated sine wave (ring modulation)
    // 3. Output 60% wet/ 40% dry mix of data to audio outputs
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // Get pointers to channelData and wetData
        auto* channelData = buffer.getWritePointer (channel);
        auto* wetData = wetBuffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Calculate value to use to modulate values in wet buffer
            if (sinFreq != sinFreqLast)
            {
                updateAngleDelta();
            }
            auto currentSinSample = (float) std::sin(currentAngle);
            currentAngle += angleDelta;
            // Modulate wetData sample value with sine wave sample value
            //wetData[sample] = wetData[sample] * currentSinSample;
            wetData[sample] = wetData[sample] * currentSinSample;
            
            // Gain staging and output.  Creating new sample value in channelData
            // By scaling down and summing the wetData (modulated) sample value
            // and the channelData (input) sample value.
            
            // The 8Hz sine wave modulates the input such that it is heard as a strong 16Hz
            // pulse.  This is quite an extreme effect, but could be useful to produce
            // interesting transformations for sci-fi, avant garde, and electronica-type
            // sounds
            
            //channelData[sample] = wetData[sample] * 0.6f + channelData[sample] * 0.4f;
            
            channelData[sample] = channelData[sample] * (1.0f - mixLevel.getNextValue()) +
                wetData[sample] * mixLevel.getNextValue();
            //channelData[sample] = channelData[sample] * (1.0f - mixLevel) +
              //  wetData[sample] * mixLevel;
            // could also have a slider just to control overall mix level
            //channelData[sample] = wetData[sample] * mixLevel;
            sinFreqLast = sinFreq;
        }
    }
    //dsp::AudioBlock<float> output(buffer);
    //gain.process(dsp::ProcessContextReplacing<float> (output));
}

//==============================================================================
bool A2_dromgoolAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* A2_dromgoolAudioProcessor::createEditor()
{
    return new A2_dromgoolAudioProcessorEditor (*this);
}

//==============================================================================
void A2_dromgoolAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void A2_dromgoolAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// User functions

void A2_dromgoolAudioProcessor::updateAngleDelta()
{
    // Calculate number of cycles that we will need to complete for each output sample
    // auto cyclesPerSample = sinFreq / currentSampleRate;
    auto cyclesPerSample = sinFreq / currentSampleRate;
    // multiply this by the length of the whole sine wave cycle
    angleDelta = cyclesPerSample * MathConstants<float>::twoPi;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A2_dromgoolAudioProcessor();
}
