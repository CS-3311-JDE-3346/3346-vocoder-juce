/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Vocoder.h"
#include "Tests/TestsHeader.h"

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#endif

void startupMsg();
void loop(const juce::ArgumentList& args);

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
            Tests::RunAllTests();
        }
    });
    app.addCommand({
        "--run|-r",
        "--run | -r",
        "Run vocoder",
        "Voclib will produce an output to Assets/out",
        [](const auto& args)
        {
            std::cout << "Not implemented yet" << std::endl;
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

int main_em(int command)
{
    std::cout << "Mode: " << command << std::endl;
    switch (command)
    {
    case 0:
    {
        char* argv[] = { "-v" };
        main(1, { argv });
    }
        break;
    case 1:
    {
        char* argv[] = { "-r" };
        main(1, { argv });
    }
        break;
    default:
        main(0, nullptr);
    }
}

#ifdef EMSCRIPTEN
//EMSCRIPTEN_BINDINGS(vocoder)
//{
//    emscripten::function("main", &main, emscripten::allow_raw_pointers());
//}
EMSCRIPTEN_BINDINGS(vocoder)
{
    emscripten::function("main_em", &main_em);
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