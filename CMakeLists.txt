cmake_minimum_required(VERSION 3.12)

project(Guitar-FX)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
