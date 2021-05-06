cmake_minimum_required(VERSION 3.12)

project(zero-pedal LANGUAGES C CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# Let CMake find manually exported modules by this project
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Find required libraries
find_package(bcm2835 REQUIRED)
find_package(guitar_fx_lib CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE include ${BCM2835_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} bcm2835::bcm2835
                                      guitar_fx_lib::guitar_fx_lib
)