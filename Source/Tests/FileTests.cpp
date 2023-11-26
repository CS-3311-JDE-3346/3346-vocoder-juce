/*
  ==============================================================================

    FileTests.cpp
    Created: 26 Nov 2023 12:33:28am
    Author:  Cinna

  ==============================================================================
*/

#include "FileTests.h"

namespace Tests_Files
{

    void Tests_Run()
    {
        Vocoder v;
        std::cout << "=================" << std::endl;
        std::cout << "Running FileTests" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Running Test_ModulatorLoad: " << Test_ModulatorLoad(v) << std::endl;
        std::cout << "Running Test_CarrierLoad: " << Test_CarrierLoad(v) << std::endl;
        //std::cout << "Running Test_FileSave: " << Test_FileSave(v) << std::endl;
        std::cout << std::endl;
    }

    bool Test_ModulatorLoad(Vocoder& v)
    {
        std::cout << "\nModulator sample filepaths:" << std::endl;
        for (juce::String i : v.modulatorSamples)
        {
            std::cout << v.defaultInputPath + i << ' ';
        }
        std::cout << std::endl;

        for (int i = 0; i < v.modulatorSamples.size(); i++)
        {
            v.loadModulatorSampleFile(v.defaultInputPath + v.modulatorSamples[i]);
            if (v.readerSourceModulator == nullptr)
            {
                return false;
            }
        }
        return true;
    }

    bool Test_CarrierLoad(Vocoder& v)
    {
        std::cout << "\nCarrier sample filepaths:" << std::endl;
        for (juce::String i : v.carrierSamples)
        {
            std::cout << v.defaultInputPath + i << ' ';
        }
        std::cout << std::endl;

        for (int i = 0; i < v.carrierSamples.size(); i++)
        {
            v.loadCarrierSampleFile(v.defaultInputPath + v.carrierSamples[i]);
            if (v.readerSourceCarrier == nullptr)
            {
                return false;
            }
        }
        return true;
    }

    bool Test_FileSave(Vocoder& v)
    {
        return true;
    }

}