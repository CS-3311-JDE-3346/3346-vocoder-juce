# vocoder-juce

Compilation must be done either in Linux or in WSL.

## Subtle changes to juce_emscripten

If compiling in WSL, make sure the following changes are made to the juce_empscripten module code.

### juce_emscripten/modules/juce_product_unlocking/marketplace/juce_OnlineUnlockStatus.cpp

```cpp
// line 282
#elif JUCE_LINUX || JUCE_EMSCRIPTEN
```

### juce_emscripten/modules/juce_core/native/juce_BasicNativeHeaders.h

```cpp
// copy and paste the section under `#elif JUCE_LINUX || JUCE_EMSCRIPTEN` including that line
// remove `|| JUCE_EMSCRIPTEN` from the original and remove `JUCE_LINUX ||` from the copy
// then remove the following includes:
#include <sys/prctl.h>
#include <sys/ptrace.h>
```

## Setup Clang
https://ubuntuhandbook.org/index.php/2023/09/how-to-install-clang-17-or-16-in-ubuntu-22-04-20-04/

## Setup Emscripten

Instructions to setup Emscripten environment can be found here: https://emscripten.org/docs/getting_started/downloads.html
Note that the Windows instructions to enter the environment may be out of date. To use the Emscripten Command Promopt, navigate to `./emsdk` and run `emcmdprompt.bat`. If you are using PowerShell, you can instead run `emsdk_env.ps1`.

### Emscripten Windows Terminal Profile

To setup a Windows Terminal instance using PowerShell, duplicate the PowerShell profile, then add the following command-line args:

```powershell
-WorkingDirectory "<pathto>\emsdk" -NoExit -Command ".\emsdk_env.ps1"
```

## Setup JUCE_emscripten

- `git clone https://github.com/Dreamtonics/juce_emscripten.git`
- todo

## Compiling with Emscripten

- todo