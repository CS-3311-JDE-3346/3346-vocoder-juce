/*
  ==============================================================================

    FileTests.cpp
    Created: 26 Nov 2023 12:33:28am
    Author:  Cinna

  ==============================================================================
*/

#include "FileTests.h"
#include<iostream>
#include<fstream>

namespace Tests_Files
{

    void Tests_Run()
    {
        Vocoder v;
        std::cout << "=================" << std::endl;
        std::cout << "Running FileTests" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Running Test_ModulatorLoad:\n" << (Test_ModulatorLoad(v) ? ">>> Passed" : ">>> Failed") << "\n---" << std::endl;
        std::cout << "Running Test_CarrierLoad:\n" << (Test_CarrierLoad(v) ? ">>> Passed" : ">>> Failed") << "\n---" << std::endl;
        std::cout << "Running Test_FileSave: " << (Test_FileSave(v) ? ">>> Passed" : ">>> Failed") << "\n---" << std::endl;
        std::cout << std::endl;
    }

    bool Test_ModulatorLoad(Vocoder& v)
    {
        std::cout << "Modulator sample filepaths:" << std::endl;
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
        std::cout << "Carrier sample filepaths:" << std::endl;
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

        //#ifdef EMSCRIPTEN
        //// MOUNT FILESYSTEM
        //EM_ASM(
        //    // Make a directory other than '/'
        //    FS.mkdir('/disk');
        //    // Then mount with IDBFS type
        //    FS.mount(IDBFS, {}, '/disk');
        //    // default MEMFS
        //    //FS.mount(MEMFS, {}, '/disk');

        //    // Then sync
        //    FS.syncfs(true, function(err) {
        //        // Error
        //    });
        //);
        //#endif

        // * C way
        char* openMode = "wb";
        //char* openMode = "rb";
        char* filePath = "./Assets/out/testOutC.wav";
        //char* filePath = "./Assets/modulator_f32_mono.wav";
        std::cout << "openMode = " << openMode << std::endl;
        FILE* pFile;

        #if defined(_MSC_VER) && _MSC_VER >= 1400
            if (fopen_s(&pFile, filePath, openMode) != 0) {
                std::cout << "MSC, fopen failed" << std::endl;
                return false;
            }
        #else
        pFile = fopen(filePath, openMode);
        if (pFile == NULL) {
            std::cout << "fopen failed" << std::endl;
            return false;
        }
        #endif

        // * C++ way
        std::string filePath2 = "./Assets/out/testOutCpp.wav";

        std::ofstream fileOut{ filePath2, std::ios::out | std::ios::binary };

        // mainly for opening files
        /*if (!fileOut.is_open()) {
            std::cerr << "Error opening file at " << filePath;
            perror(" ");
        }*/

        char* blah = "0101";
        fileOut.write(blah, sizeof(char) * strlen(blah));

        // failbit can be set by getline if it cannot extract data
        // this can often happen if the last char in a file is a lin delimiter
        // only when bad bit is set will errno be updated and we know there's an exception
        if (fileOut.bad()) {
            std::string errorBuffer;
            //size_t buffSize = strerrorlen_s();
            // strerror is not threadsafe, but can't use strerror_s:
            // msvc seems to be missing strerrorlen_s
            std::cerr << "Error while reading file at " << filePath;
            perror(" ");
            return false;
        }
        //stream.close(); // not needed, destructor will call this automatically

        return true;
    }
}