/*
  ==============================================================================

    FileTests.h
    Created: 26 Nov 2023 12:33:28am
    Author:  Cinna

  ==============================================================================
*/

#pragma once
#include "../Vocoder.h"

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

namespace Tests_Files
{

    void Tests_Run();

    bool Test_ModulatorLoad(Vocoder& v);
    bool Test_CarrierLoad(Vocoder& v);
    bool Test_FileSave(Vocoder& v);

}