/*
  ==============================================================================

    Vocoder.h
    Created: 25 Nov 2023 3:16:22pm
    Author:  DerputeR

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>

class Vocoder
{
public:
    static juce::String defaultInputPath;
    static juce::String defaultOutputPath;
    static juce::String defaultModulatorSample;
    static juce::String defaultCarrierSample_Sine;
    static juce::String defaultCarrierSample_Saw;
    static juce::String defaultCarrierSample_Square;
    static juce::String defaultCarrierSample_Triangle;
public:
    Vocoder();
    //~Vocoder();
    std::vector<juce::String> modulatorSamples{
        defaultModulatorSample
    };
    std::vector<juce::String> carrierSamples{ 
        defaultCarrierSample_Sine,
        defaultCarrierSample_Saw,
        defaultCarrierSample_Square,
        defaultCarrierSample_Triangle
    };
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSourceCarrier;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSourceModulator;
    void loadModulatorSampleFile(const juce::String& filepath);
    void loadCarrierSampleFile(const juce::String& filepath);
};

namespace NoiseGenerator
{
    
};