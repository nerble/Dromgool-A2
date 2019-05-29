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
                       ), parameters(*this, nullptr, Identifier("A2-Dromgool"),
                                {
                                    // List of parameters for plugin
                                    // params for buttons etc go here
                                    // 'nullptr' above is where you would inform processor if you had an undo manager
                                    std::make_unique<AudioParameterFloat>("mix", // parameter ID
                                                                          "Mix", // parameter Name in DAW dropdown
                                                                          0.0f, // min value
                                                                          1.0f, // max value
                                                                          0.5f // default value
                                                                          ),
                                    std::make_unique<AudioParameterFloat>("freq",
                                                                        "Modder",
                                                                        0.0f,
                                                                        9000.0f,
                                                                        0.0f
                                                                        ),
                                    std::make_unique<AudioParameterFloat>("bit",
                                                                          "Crusher",
                                                                          1,
                                                                          16,
                                                                          16
                                                                          ),
                                    std::make_unique<AudioParameterFloat>("dist",
                                                                          "Squasher",
                                                                          0.0f,
                                                                          0.5f,
                                                                          1.0f
                                                                          )
                                }
                    )

#endif
{
    // initialise some global variables
    mixParameter = parameters.getRawParameterValue("mix");
    freqParameter = parameters.getRawParameterValue("freq");
    bitParameter = parameters.getRawParameterValue("bit");
    distParameter = parameters.getRawParameterValue("dist");
    
    currentSampleRate     = 0.0f;
    currentAngle          = 0.0f;
    angleDelta            = 0.0f;
    sinFreq               = *freqParameter;
    distLevel             = *distParameter;
    bitLevel              = *bitParameter;
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
    sinFreq = *freqParameter;
    distLevel = *distParameter;
    bitLevel = *bitParameter;
    mixLevel = *mixParameter;
    updateAngleDelta();
    
    String message;
    message << "Preparing to play..." << newLine;
    message << "My sample rate is: " << currentSampleRate << newLine;
    message << "My sine wave frequency is " << sinFreq << "Hz" << newLine;
    message << "My distortion level is " << distLevel << newLine;
    message << "My bit depth is " << bitLevel << newLine;
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
    // 2. Manipulate samples using effects (ring mod, bitcrusher, distortion)
    // 3. Output mix of data to audio outputs
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // Get pointers to channelData and wetData
        auto* channelData = buffer.getWritePointer (channel);
        auto* wetData = wetBuffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            //
            // Ring modulator processing
            //
            
            // Calculate value to use to modulate values in wet buffer
            
            if (sinFreq != sinFreqLast)
            {
                updateAngleDelta();
            }
            auto currentSinSample = (float) std::sin(currentAngle);
            currentAngle += angleDelta;
            
            
            // Modulate wetData sample value with sine wave sample value
            
            if (sinFreq > 0.0f)
            {
                wetData[sample] = wetData[sample] * currentSinSample;
            }
            
            
            // Bitcrusher.  See: https://www.musicdsp.org/en/latest/Effects/124-decimator.html
            //
            
            if (bitLevel < 16)
            {
                float quantum = powf(2.0f, bitLevel);
                auto shapedSample = floor(wetData[sample] * quantum) / quantum;
                wetData[sample] = shapedSample;
            }
            
            
            //
            // Fold-back distortion ("squasher") effect.  See: https://www.musicdsp.org/en/latest/Effects/203-fold-back-distortion.html
            //
            
            if (distLevel < 1.0f && distLevel > 0.0f)
            {
                wetData[sample] = fabs(fabs(fmod(wetData[sample] - distLevel, distLevel*4)) - distLevel*2) - distLevel;
                float scaleGain = jmap(distLevel, 2.0f, 0.0f); // scale amplitude up depending on how much you squash it.  With slider at far left basically it's hiss.
                wetData[sample] = wetData[sample] + scaleGain;
            }
            
            
            //
            // Wet/Dry mix
            //
            
            channelData[sample] =  channelData[sample] * (1.0f - mixLevel) + wetData[sample] * mixLevel;
            
            sinFreqLast = sinFreq;
        }
    }
}

//==============================================================================
bool A2_dromgoolAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* A2_dromgoolAudioProcessor::createEditor()
{
    return new A2_dromgoolAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void A2_dromgoolAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // Copy current state of valuetree
    
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void A2_dromgoolAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(ValueTree::fromXml(*xmlState));
        }
    }
}
//==============================================================================
// User functions

void A2_dromgoolAudioProcessor::updateAngleDelta()
{
    // Calculate number of cycles that we will need to complete for each output sample
    
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

