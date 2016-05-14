MPGROMDUMP 1.0 FINAL
-------------------------

Dependencies
------------
Everything was compiled using the kpit elf compiler and the Iapetus library. Iapetus itself is downloaded from github if it isn't already present. You will need to compile some kind of SH2 cross compiler beforehand. Otherwise everything else should be detected using cmake.

Build Instructions
------------------
1. Start up cmake-gui.
2. Set "Where is the source code" to where you downloaded source code to.
3. Set "Where to build the binaries" to another directory, ideally not the same directory as source code. Make a note of directory.
4. Click on "Configure" and answer yes to create directory if it doesn't exist. 
5. For generator you should be using "Unix Makefiles" or something equivalent. Make sure "Specify toolchain file for cross-compiling". Click "Next".
6. For toolchain file go to "Platform" subdirectory in source code directory and select "SegaSaturn".
7. If there's any errors, correct them. Otherwise click "Generate" button.
8. Close cmake.
9. On the command-line, go into binaries directory you made note of above and type: "make".
10. If everything is successful you should get a message "[100%] Built target MPGROMDUMP". The final binary is called "MPGROMDUMP.BIN" is is located in the binaries directory.

Usage Instruction
-----------------
1. Make sure your Action Replay is inserted while the Saturn is off.
2. Turn on Saturn and load MPGROMDUMP.
3. The program will detect your mpeg card and dump the rom to ram. When you see "COMPLETE" message, that means you can dump the ram to PC from your communication utility.

Special Thanks
--------------
Thanks to my buds on #yabause, #mednafen, rhdn, and assemblergames
