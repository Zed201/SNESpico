#!/bin/bash
BASE_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
PICO_SDK="$BASE_DIR/vendor/pico-sdk"

cp $PICO_SDK/external/pico_sdk_import.cmake  .

# definir o PICO_SDK_PATH
export PICO_SDK_PATH="$PICO_SDK"

rm -rf ./build && mkdir build
cd build
cmake ..
make