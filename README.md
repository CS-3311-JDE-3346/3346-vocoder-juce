# vocoder-juce

Compilation must be done either in Linux or in WSL

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