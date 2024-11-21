# /bin/bash
cp vendor/pico-sdk/external/pico_sdk_import.cmake  .
mkdir build
cd build
cmake ..
make