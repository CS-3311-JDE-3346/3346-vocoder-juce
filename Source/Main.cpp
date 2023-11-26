/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Vocoder.h"
#include "Tests/TestsHeader.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

void startupMsg();
void loop(const juce::ArgumentList& args);

//==============================================================================
int main (int argc, char* argv[])
{
    juce::ConsoleApplication app;
    app.addHelpCommand("--help|-h", "Usage:", true);
    app.addVersionCommand("--version|-v", "Vocoder (Headless) v0.01");
    app.addCommand({
        "--tests|-t",
        "--tests | -t",
        "Run tests",
        "Run unit-like tests",
        [](const auto& args) {}
    });
    app.addDefaultCommand({"-c", "-c", "Runs the vocoder in continuous mode (default)", "Runs the vocoder in continuous mode (default)", [](const auto& args) { loop(args); }
});
    return app.findAndRunCommand(argc, argv);
}

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