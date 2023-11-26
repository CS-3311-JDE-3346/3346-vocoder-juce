/*
  ==============================================================================

    FileTests.h
    Created: 26 Nov 2023 12:33:28am
    Author:  Cinna

  ==============================================================================
*/

#pragma once
#include "../Vocoder.h"

bool Tests_Run();

bool Test_ModulatorLoad(const Vocoder& v);
bool Test_CarrierLoad(const Vocoder& v);
bool Test_FileSave(const Vocoder& v);
