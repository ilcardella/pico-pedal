cmake_minimum_required(VERSION 3.12)

# PICO_SDK_PATH env var must point to the sdk installation path
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(pico-pedal LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(guitar_fx_lib CONFIG REQUIRED)

pico_sdk_init()

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/pico_pedal_main.cpp
                                        src/adc.cpp
                                        src/audio_pwm.cpp
                                        src/button.cpp
                                        src/display.cpp
                                        src/potentiometer.cpp
                                        src/led.cpp
                                        src/pico_pedal.cpp
                                        src/switch.cpp
                                        src/ssd1306/GFX.cpp
                                        src/ssd1306/SSD1306.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
                        pico_stdlib
                        hardware_adc
                        hardware_i2c
                        hardware_pwm
                        hardware_spi
                        guitar_fx_lib::guitar_fx_lib
)

# Enable USB serial output and disable UARTS
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})
