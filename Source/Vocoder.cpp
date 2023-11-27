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

#ifdef EMSCRIPTEN
#include <emscripten.h>
#include <emscripten/bind.h>
#endif

juce::String Vocoder::defaultInputPath = "./Assets/";
juce::String Vocoder::defaultOutputPath = "./Assets/out/";
juce::String Vocoder::customModulatorSample = "silence.wav";
juce::String Vocoder::customCarrierSample = "silence.wav";
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

bool Vocoder::setModulatorIndex(int index)
{
    if (index > -1 && index < this->modulatorSamples.size())
    {
        this->modulatorIndex = index;
        return true;
    }
    return false;
}

bool Vocoder::setCarrierIndex(int index)
{
    if (index > -1 && index < this->carrierSamples.size())
    {
        this->carrierIndex = index;
        return true;
    }
    return false;
}

int Vocoder::getModulatorIndex() const
{
    return this->modulatorIndex;
}

int Vocoder::getCarrierIndex() const
{
    return this->carrierIndex;
}

bool Vocoder::setModulatorFilename(const juce::String& filename)
{
    if (filename.length() > 0)
    {
        this->modulatorSamples[0] = filename;
        return true;
    }
    return false;
}

bool Vocoder::setCarrierFilename(const juce::String& filename)
{
    if (filename.length() > 0)
    {
        this->carrierSamples[0] = filename;
        return true;
    }
    return false;
}

class Blah
{
    int x;
public:
    Blah(int x) {
        this->x = x;
    }
};

#ifdef EMSCRIPTEN
EMSCRIPTEN_KEEPALIVE
EMSCRIPTEN_BINDINGS(vocoder)
{
    emscripten::class_<Vocoder>("Vocoder")
        .constructor<>()
        .function("setModulatorFilename", &Vocoder::setModulatorFilename)
        .function("setCarrierFilename", &Vocoder::setCarrierFilename)

        .property("carrierIndex", &Vocoder::getCarrierIndex, &Vocoder::setCarrierIndex)
        .property("modulatorIndex", &Vocoder::getModulatorIndex, &Vocoder::setModulatorIndex)
        ;
}
#endif