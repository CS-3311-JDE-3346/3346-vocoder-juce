1. [x] Initialize projucer project
2. [x] Read in wav files
	1. [x] Parse other audio filetypes to behave same as with wav files
	2. [ ] Get duration of file
	3. [ ] Force to 44.1kHz sample rate
	4. [ ] Force to mono signal (for now)
3. [ ] Generate noise -> wav file
	1. [ ] Match length of modulator signal
4. [ ] Generate basic waveforms -> wav file
	1. [ ] #future MIDI file parser -> Generate basic waveforms -> wav file
5. [ ] Use voclib to perform vocoding
6. [ ] Construct basic HTML page to upload input MIDI & input modulator; select carrier signal waveform
7. [ ] Bind input and output functions for JS
8. [ ] Update README.md with notes
9. [ ] Hook up with front end

## docs

### projucer project setup

>[!caution] Ensure Projucer Linux path is set to point to `juce_emscripten`

compiler flags:

```
-std=c++17
-sUSE_PTHREADS=1 -sDISABLE_EXCEPTION_CATCHING=0
```

linker flags:

```
-o vocoder.html
```

if using Projucer (emprofile), no need to modify Emscripten Makefile. If using normal Projucer, make sure the Emscripten makefile has no references or uses of PKG_CONFIG

Add include directory for IntelliSense:
MAKE SURE TO WRAP ANY EMSCRIPTEN-SPECIFIC CODE WITH GUARDS (check if `EMSCRIPTEN` is defined)

```
emsdk/upstream/emscripten/system/include/emscripten
G:\Dev\web\emscripten\emsdk\upstream\emscripten\system\include\emscripten
```

## read in wav files

>[!caution] Make sure to copy the Assets folder to be next to the built binary to access the debug samples
>In the future it's possible to turn the debug samples into binary data to embed into the binary at compile time