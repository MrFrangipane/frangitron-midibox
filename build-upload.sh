cd ~/frangitron/frangitron-midibox
make -j8
cd ~/midibox/mios32/trunk/tools/mios_studio/Builds/Linux/build
./MIOS_Studio_Debug --upload_hex=/home/frangi/frangitron/frangitron-midibox/project.hex

