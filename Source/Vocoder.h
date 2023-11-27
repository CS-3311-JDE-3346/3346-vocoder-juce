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
    int modulatorIndex = 0;
    int carrierIndex = 0;
public:
    // static members must be initialized in the implementation (see Vocoder.cpp)
    static juce::String defaultInputPath;
    static juce::String defaultOutputPath;
    static juce::String customModulatorSample;
    static juce::String defaultModulatorSample;
    static juce::String customCarrierSample;
    static juce::String defaultCarrierSample_Sine;
    static juce::String defaultCarrierSample_Saw;
    static juce::String defaultCarrierSample_Square;
    static juce::String defaultCarrierSample_Triangle;
public:
    Vocoder();
    //~Vocoder();
    std::vector<juce::String> modulatorSamples{
        customModulatorSample,
        defaultModulatorSample
    };
    std::vector<juce::String> carrierSamples{ 
        customCarrierSample,
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
    bool setModulatorIndex(int index);
    bool setCarrierIndex(int index);
    int getModulatorIndex() const;
    int getCarrierIndex() const;
    // using std::string for js-exposed functions since otherwise I would have to somehow do a type conversion from JS string to juce::String
    // which would probably involve somehow exporting juce::String and I would prefer to just stick to built-in types
    bool setModulatorFilename(const std::string& filename);
    bool setCarrierFilename(const std::string& filename);
    bool run();
};

namespace NoiseGenerator
{
    
};