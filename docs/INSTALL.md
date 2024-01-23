
This project has been tested for a fresh install of Ubuntu 22.04 LTS running on WSL 2. To check the version of an existing Ubuntu distro, within an Ubuntu shell:

```bash
lsb_release -a
```

To install a fresh copy of Ubuntu 22.04 for WSL 2, in Command Prompt or PowerShell:

```PowerShell
wsl --install Ubuntu-22.04
```

To enter WSL, do:

```PowerShell
# In Windows:
wsl --distribution Ubuntu-22.04
```

Or, if you wish to upgrade an existing version (this may take some time):

```bash
# In Ubuntu:
sudo apt update && sudo apt full-upgrade
exit
```

```PowerShell
# In Windows:
wsl --terminate Ubuntu # replace Ubuntu with the name of your distro if needed
wsl
```

```bash
# In Ubuntu:
sudo do-release-upgrade
```

If you only have one install of WSL, simply run `wsl` to enter the distro. All future commands, unless otherwise specified, will be within this distro.

It is usually a good idea to make sure currently installed packages are up to date:

```bash
sudo apt-get update
sudo apt-get upgrade
```

It is recommended that everything be kept in a dedicated `dev` directory. For ease of documentation, we will run these commands:

```bash
cd ~
mkdir dev
cd dev
mkdir projects
mkdir lib
mkdir tools
```

These will create directories for ease of organization. We will be using these directories throughout this documentation.

## GitHub authentication

### Git for Windows is already installed and in-use

Git Credential Manager can be linked with WSL's Git by following the instructions found here: https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git#git-credential-manager-setup

### Git for Windows is not installed

An easy solution is to install the GitHub Command Line tool: https://github.com/cli/cli/blob/trunk/docs/install_linux.md

Then follow the instructions here to authenticate with your GitHub account: https://cli.github.com/manual/gh_auth

# Project setup

Installation of project dependencies will be in the following order:

1. Emscripten
2. JUCE-emmake
3. juce_emscripten
4. vocoder-juce

#### Aside: Windows-local project installation

For consistency and ease of following along, the repo for `vocoder-juce` will be cloned to the WSL Ubuntu filesystem. However, it is possible to clone it locally link it to WSL Ubuntu from the Windows filesystem.

This will not be discussed in detail for the sake of brevity, but as a general guideline:

- Wherever you need a Windows path in WSL, replace `drive-letter:` with `/mnt/drive-letter` and all backslashes `\` with forward slashes `/`. 
	- Example: `C:\dev` -> `/mnt/c/dev`
- Wherever you need a WSL path in Windows, you can type `explorer .` in the directory you need and copy the path from the URL bar in Windows File Explorer

## Emscripten installation

```bash
cd ~/dev/tools
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
```

To enable Emscripten from anywhere:

```bash
source $HOME/dev/tools/emsdk/emsdk_env.sh
```

This will set the appropriate environment variables and enable use of commands like `emmake`, `emcc`, and `em++`.

It is recommended to make a Bash alias for ease of use. If you do not already having a `.bash_aliases` file in your home directory (check by running `ls -hal ~`), create one first:

```bash
cd ~
touch .bash_aliases
```

Then add the alias to this file:

```bash
echo alias emscripten="'source \"$HOME/dev/tools/emsdk/emsdk_env.sh\"'" >> "$HOME/.bash_aliases"
```

This allows you to run the alias `emscripten` in any future Bash current instead of typing the full `source` command from before. To enable access to new aliases in the current session:

```bash
. .bash_aliases
```

Alternatively, logging out of WSL (`exit`) and logging back in (`wsl --distribution Ubuntu-22.04`, or simply `wsl` if this is your only distro) will load the new aliases.

## JUCE-emmake

Ensure you have the following packages installed:

```bash
sudo apt install build-essential
sudo apt install pkgconf

sudo apt install libasound2-dev libjack-jackd2-dev \
    ladspa-sdk \
    libcurl4-openssl-dev  \
    libfreetype6-dev \
    libx11-dev libxcomposite-dev libxcursor-dev libxcursor-dev libxext-dev libxinerama-dev libxrandr-dev libxrender-dev \
    libwebkit2gtk-4.0-dev \
    libglu1-mesa-dev mesa-common-dev
```

Note that if you wish to rebuild any of the tooling, you will need to install CMake. This topic is outside the scope of this documentation.

```bash
cd ~/dev/lib
git clone https://github.com/CS-3311-JDE-3346/JUCE-emmake.git
cd JUCE-emmake/extras/Projucer/Builds/LinuxMakefile
make
cd build
```

Running the output program `Projucer` will allow you to configure and export `.jucer` project source configurations. It may be handy to make `Projucer` an alias:

```bash
echo alias Projucer="'$HOME/dev/lib/JUCE-emmake/extras/Projucer/Builds/LinuxMakefile/build/Projucer'" >> "$HOME/.bash_aliases"
```

## juce_emscripten

```bash
cd ~/dev/lib
git clone https://github.com/Dreamtonics/juce_emscripten.git
```

A few changes are needed to ensure compilation via Emscripten works:


### juce_OnlineUnlockStatus.cpp

```bash
cd $HOME/dev/lib/juce_emscripten/modules/juce_product_unlocking/marketplace
```

Open `juce_OnlineUnlockStatus.cpp` and make the following change. If you are uncomfortable using CLI text editors like `nano` or `vim`, you can type `explorer.exe .` to open this directory in Windows File Explorer and proceed with your editor of choice.

```cpp
// replace line 282 with the following:
#elif JUCE_LINUX || JUCE_EMSCRIPTEN
```

### juce_BasicNativeHeaders.h

```bash
cd $HOME/dev/lib/juce_emscripten/modules/juce_core/native
```

Open `juce_BasicNativeHeaders.h` and follow the instructions:

```cpp
// copy and paste the section under `#elif JUCE_LINUX || JUCE_EMSCRIPTEN` including that line (lines 215-246)
// from the original elif block, remove `|| JUCE_EMSCRIPTEN`
// from the copy of the elif block, remove `JUCE_LINUX ||` and these includes:
#include <sys/prctl.h>
#include <sys/ptrace.h>
```

## vocoder-juce

We first need to configure Projucer. Launch it using the `Projucer` alias, then go to **File** -> **Global Paths**. Make sure the following configurations are set:

OS: `Linux`
Path to JUCE: `~/dev/lib/juce_emscripten`
Path to JUCE Modules: `~/dev/lib/juce_emscripten/modules`

Click **Re-scan JUCE Modules** and **Re-scan User Modules**, then untick "Warn about incorrect JUCE path". Exit out of the Global Paths dialog. Close Projucer for now.

```bash
cd ~/dev/projects
git clone https://github.com/CS-3311-JDE-3346/3346-vocoder-juce.git
```

### Setup for Building with Visual Studio 2022 Community Edition

`vocoder-juce` can presently be built to run as a standalone CLI application on Windows, which can be helpful for rapid prototyping and testing iterations. If you wish to make use of this, follow along.

```bash
cd ~/dev
explorer.exe .
```

You will need to make note of a few paths from Windows File Explorer.
First, save the Windows path to `tools/emsdk/upstream/emscripten/system/include`. It should look similar to:

```
\\wsl.localhost\Ubuntu-22.04\home\username\dev\tools\emsdk\upstream\emscripten\system\include
```

Next, save the Windows paths to `lib/juce_emscripten` and `lib/juce_emscripten/modules`:

```
\\wsl.localhost\Ubuntu-22.04\home\username\dev\lib\juce_emscripten
\\wsl.localhost\Ubuntu-22.04\home\username\dev\lib\juce_emscripten\modules
```

Back in the Ubuntu shell, execute the following:

```bash
cd ~/dev/projects/3346-vocoder-juce
Projucer VocoderJUCE_Headless.jucer
```

Inside Projucer:

1. Navigate to **Exporters** in the left panel
2. Open the **Visual Studio 2022** dropdown, then select the **Debug** profile.
3. In the "Header Search Paths" box, look to see if the full path you copied earlier is in the list. If it is not, append it.
4. Repeat step 3 but for the **Release** profile
5. Save the project (Ctrl+S or **File -> Save**)
6. Go to **File -> Global Paths**, and select "Windows" from the OS dropdown
7. Change "Path to JUCE" and "JUCE Modules" to match the Windows paths you saved earlier

You may then run `explorer.exe .` to open Windows File Explorer to the `3346-vocoder-juce` file directory. Copy the `Assets` folder, then navigate to `Builds/VisualStudio2022`. Paste the `Assets` folder here. You may now open `VocoderJUCE_Headless.sln` with Visual Studio.

If you are prompted with a dialog saying "Found a suitable location for browsing database and IntelliSense files", tick "Do not prompt me again" and click **OK**.

You should now be able to build and debug the vocoder solution locally.

**Important**: If you add any new source files, you **must** add them in Projucer, or other users who pull the repo and complete the setup will be missing these source files from their Visual Studio solution. To do so, open Projucer:

1. Open the **File Explorer** dropdown in the left panel
2. Click the **+** icon. You may add existing files or create new cpp/hpp files from here
3. Save the project, then close Projucer.
4. Re-open the solution in Visual Studio

### Building the project with Emscripten

First run the `emscripten` alias (or use the full command to initialize Emscripten), then:

```bash
cd ~/dev/projects/3346-vocoder-juce/Builds/Emscripten
emmake make
```

Once compilation and linking is finished, we can test the WebAssembly. To do so, we will use `live-server`:

```
npm install -g live-server
```

Aside: if `npm` warns you about having an outdated version, no worries: it is using the version of `npm` prepackaged with Emscripten. An update is not needed.

If you do try to update `npm`, you may encounter an error saying `Not compatible with your version of node/npm: npm`. If this is the case, you can install an updated version of `npm` and `nodejs`:

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash

export NVM_DIR="$([ -z "${XDG_CONFIG_HOME-}" ] && printf %s "${HOME}/.nvm" || printf %s "${XDG_CONFIG_HOME}/nvm")"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"

nvm install node
```

Further troubleshooting of `npm` is beyond the scope of this documentation. For more information, see:
https://github.com/nvm-sh/nvm#installing-and-updating
https://docs.npmjs.com/downloading-and-installing-node-js-and-npm
https://docs.npmjs.com/resolving-eacces-permissions-errors-when-installing-packages-globally

The next time you run the `emscripten` alias in a fresh shell, `npm` will use this updated version instead of the one pre-packaged with Emscripten.

To start the `live-server`, simply run:

```bash
live-server ./test_load.html
```

Load the listed IP address in your web browser (typically http://127.0.0.1:8080).
Further options can be found here: https://www.npmjs.com/package/live-server
