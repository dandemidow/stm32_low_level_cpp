cmake_minimum_required(VERSION 3.15)

project(ll-lib)

add_library(stll
  STATIC
    gpio/pin.cpp
    gpio/output.cpp
    gpio/input.cpp
    gpio/analog.cpp
)

target_include_directories(stll
  PUBLIC
    .
)

target_compile_options(stll
  PRIVATE
    $<$<CONFIG:Debug>:-Og>
)
