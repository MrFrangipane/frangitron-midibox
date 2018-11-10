cd ~/frangitron/frangitron-midibox/src
make -j8
cd ~/midibox/mios32/trunk/tools/mios_studio/Builds/Linux/build
./MIOS_Studio_Debug --upload_hex=~/frangitron/frangitron-midibox/src/project.hex
