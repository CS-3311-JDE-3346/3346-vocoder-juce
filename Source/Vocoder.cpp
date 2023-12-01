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
#include "Lib/shell/vocshell.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#include <emscripten/bind.h>
#endif

juce::String Vocoder::defaultInputPath = "./Assets/";
juce::String Vocoder::defaultOutputPath = "./Assets/out/";
juce::String Vocoder::customModulatorSample = "silence.wav";
juce::String Vocoder::customCarrierSample = "silence.wav";
juce::String Vocoder::defaultModulatorSample = "modulator_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Sine = "sine_220hz_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Saw = "saw_220hz_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Square = "square_220hz_f32_mono.wav";
juce::String Vocoder::defaultCarrierSample_Triangle = "triangle_220hz_f32_mono.wav";

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

bool Vocoder::setModulatorFilename(const std::string& filename)
{
    if (filename.length() > 0)
    {
        this->modulatorSamples[0] = filename;
        return true;
    }
    return false;
}

bool Vocoder::setCarrierFilename(const std::string& filename)
{
    if (filename.length() > 0)
    {
        this->carrierSamples[0] = filename;
        return true;
    }
    return false;
}

bool Vocoder::run()
{
    std::string carrierPath = (Vocoder::defaultInputPath + this->carrierSamples[this->getCarrierIndex()]).toStdString();
    std::string modulatorPath = (Vocoder::defaultInputPath + this->modulatorSamples[this->getModulatorIndex()]).toStdString();
    std::string outputPath = (Vocoder::defaultOutputPath + "output.wav").toStdString();
    std::vector<const char*> argvec{ "args", "-c", carrierPath.c_str(), "-m", modulatorPath.c_str(), "-o", outputPath.c_str() };

    std::cout << "voclib args:" << std::endl;
    for (const char* i : argvec)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    const char** argv = argvec.data();
    auto argc = argvec.size();
    if (main_Shell(argc, argv) == 0)
    {
        return true;
    }
    return false;
}


#ifdef EMSCRIPTEN
EMSCRIPTEN_KEEPALIVE
EMSCRIPTEN_BINDINGS(vocoder)
{
    emscripten::class_<Vocoder>("Vocoder")
        .constructor<>()
        .function("setModulatorFilename", &Vocoder::setModulatorFilename)
        .function("setCarrierFilename", &Vocoder::setCarrierFilename)
        .function("run", &Vocoder::run)

        .property("carrierIndex", &Vocoder::getCarrierIndex, &Vocoder::setCarrierIndex)
        .property("modulatorIndex", &Vocoder::getModulatorIndex, &Vocoder::setModulatorIndex)
        ;
}
#endif