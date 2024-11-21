cmake_minimum_required(VERSION 3.31)
include(pico_sdk_import.cmake)

project(snes C ASM CXX)
pico_sdk_init()
add_executable(snes
    main.cpp
)

target_link_libraries(snes pico_stdlib)

pico_add_extra_outputs(snes)
