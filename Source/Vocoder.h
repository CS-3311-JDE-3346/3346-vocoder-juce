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
    juce::String defaultInputPath = "../Assets/";
    juce::String defaultOutputPath = "../Assets/";
    
    juce::String defaultModulatorSample = "modulator_f32_mono.wav";
    juce::String defaultCarrierSample_Sine = "sine_440hz_f32_mono.wav";
    juce::String defaultCarrierSample_Saw = "saw_440hz_f32_mono.wav";
    juce::String defaultCarrierSample_Square = "square_440hz_f32_mono.wav";
    juce::String defaultCarrierSample_Triangle = "triangle_440hz_f32_mono.wav";
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
    void loadCarrierSampleFile(const juce::String& filepath)
};

namespace NoiseGenerator
{
    
};