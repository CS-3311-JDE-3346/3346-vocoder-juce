/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Vocoder.h"
#include <string>
#include "Tests/TestsHeader.h"
#include "Lib/shell/vocshell.h"

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#endif

void startupMsg();
void loop(const juce::ArgumentList& args);
void runVocoder();

//==============================================================================
#ifdef EMSCRIPTEN
EMSCRIPTEN_KEEPALIVE
#endif
int main (int argc, char* argv[])
{
    juce::ConsoleApplication app;
    app.addHelpCommand("--help|-h", "Usage:", true);
    app.addVersionCommand("--version|-v", "Vocoder (Headless) v0.01");
    app.addDefaultCommand({
        "--tests|-t",
        "--tests | -t",
        "Run tests",
        "Run unit-like tests",
        [](const auto& args)
        {
            Tests::runAllTests();
        }
    });
    app.addCommand({
        "--run|-r",
        "--run | -r",
        "Run vocoder",
        "Voclib will produce an output to Assets/out",
        [](const auto& args)
        {
            runVocoder();
        }
    });
    app.addCommand({
        "-c",
        "-c",
        "Runs the vocoder in continuous mode",
        "Runs the vocoder in continuous mode (not yet implemented)",
        [](const auto& args)
        {
            loop(args);
        }
    });
    return app.findAndRunCommand(argc, argv);
}

void runVocoder()
{
    Vocoder vocoder;
    std::string carrierPath = (Vocoder::defaultInputPath + vocoder.carrierSamples[vocoder.getCarrierIndex()]).toStdString();
    std::string modulatorPath = (Vocoder::defaultInputPath + vocoder.modulatorSamples[vocoder.getModulatorIndex()]).toStdString();
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
    main_Shell(argc, argv);
}

#ifdef EMSCRIPTEN
//EMSCRIPTEN_BINDINGS(vocoder)
//{
//    emscripten::function("main", &main, emscripten::allow_raw_pointers());
//}
EMSCRIPTEN_BINDINGS(main)
{
    emscripten::function("runVocoder", &runVocoder);
}
#endif


void startupMsg() {
    std::cout << "Initializing vocoder" << std::endl;
#ifdef EMSCRIPTEN
    std::cout << "Detected WASM MODE" << std::endl;
#endif
}

void loop(const juce::ArgumentList& args)
{
    startupMsg();
    // avoid infinite loop if executing as wasm
    bool wasm = false;
#ifdef EMSCRIPTEN
    wasm = true;
#endif
    while (!wasm)
    {

    }
}