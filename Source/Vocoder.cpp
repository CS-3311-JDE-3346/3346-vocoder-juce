/*
  ==============================================================================

    Vocoder.cpp
    Created: 25 Nov 2023 3:16:22pm
    Author:  DerputeR

  ==============================================================================
*/

#include "Vocoder.h"
#include <iostream>
#include <JuceHeader.h>

juce::String Vocoder::defaultInputPath = "./Assets/";
juce::String Vocoder::defaultOutputPath = "./Assets/out/";
juce::String Vocoder::defaultModulatorSample = "modulator_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Sine = "sine_440hz_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Saw = "saw_440hz_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Square = "square_440hz_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Triangle = "triangle_440hz_f32_mono.wav";

Vocoder::Vocoder()
{
    formatManager.registerBasicFormats();
}

void Vocoder::loadModulatorSampleFile(const juce::String& filepath)
{
    juce::File file{ filepath };
    std::cout << "Filepath generated: " << file.getFullPathName() << std::endl;
    if (file != juce::File{}) // file is not invalid
    {
        juce::AudioFormatReader* reader = formatManager.createReaderFor(file);
        if (reader != nullptr)
        {
            auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            readerSourceModulator.reset(newSource.release());
        }
    }
}

void Vocoder::loadCarrierSampleFile(const juce::String& filepath)
{
    juce::File file{ filepath };
    std::cout << "Filepath generated: " << file.getFullPathName() << std::endl;
    if (file != juce::File{}) // file is not invalid
    {
        juce::AudioFormatReader* reader = formatManager.createReaderFor(file);
        if (reader != nullptr)
        {
            auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            readerSourceCarrier.reset(newSource.release());
        }
    }
}
