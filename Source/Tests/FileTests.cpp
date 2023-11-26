/*
  ==============================================================================

    FileTests.cpp
    Created: 26 Nov 2023 12:33:28am
    Author:  Cinna

  ==============================================================================
*/

#include "FileTests.h"

bool Tests_Run()
{
    Vocoder v;
    if (Test_ModulatorLoad(v) && Test_CarrierLoad(v) && Test_FileSave(v))
    {
        return true;
    }
    return false;
}

bool Test_ModulatorLoad(const Vocoder& v)
{
    
    return false;
}

bool Test_CarrierLoad(const Vocoder& v)
{
    return false;
}

bool Test_FileSave(const Vocoder& v)
{
    return false;
}
