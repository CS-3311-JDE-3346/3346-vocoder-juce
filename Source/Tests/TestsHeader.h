/*
  ==============================================================================

    TestsHeader.h
    Created: 26 Nov 2023 12:36:05am
    Author:  Cinna

  ==============================================================================
*/

#pragma once
#include "FileTests.h"

namespace Tests
{
    void RunAllTests()
    {
        Tests_Files::Tests_Run();
    }
}