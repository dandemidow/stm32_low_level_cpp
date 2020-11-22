cmake_minimum_required(VERSION 3.15)

project(ll-lib)

add_library(stll
  STATIC
    gpio.cpp
)

target_include_directories(stll
  PUBLIC
    .
)

target_compile_definitions(stll
  PUBLIC
    STM32L452
)

target_compile_options(stll
  PRIVATE
    -march=armv7e-m
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -fdata-sections
    -ffunction-sections
    -Wall
    -Wextra
    -Wno-volatile       #for a while disable this warning
    -fmessage-length=0
    -fno-exceptions
    -fno-rtti
    $<$<CONFIG:Debug>:-Og>
)
