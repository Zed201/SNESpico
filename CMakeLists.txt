cmake_minimum_required(VERSION 3.22) 
# verificar a versão para ele poder ser rodado em outros sistemas
# o 3.31 tem no arch mas não no ubuntu

# inclue algumas coisas do pico
include(pico_sdk_import.cmake)

project(SNESpico)

pico_sdk_init()

add_executable(SNESpico
    main.cpp
)

# adicionar as libs de features específicas
target_link_libraries(SNESpico pico_stdlib 
hardware_pwm hardware_adc pico_multicore pico_sync)

pico_enable_stdio_usb(SNESpico 1)
pico_enable_stdio_uart(SNESpico 0)

# criar o map/bin/hex/uf2 
pico_add_extra_outputs(SNESpico)