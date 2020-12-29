cmake_minimum_required(VERSION 3.15)

project(stm32-ll-lib)

add_library(stm32ll
  STATIC
    gpio/pin.cpp
    gpio/output.cpp
    gpio/input.cpp
    gpio/analog.cpp
)

target_include_directories(stm32ll
  PUBLIC
    .
)

target_compile_options(stm32ll
  PRIVATE
    "${ARCH}"
    "${COMMON_OPTS}"
)
