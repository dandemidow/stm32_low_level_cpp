cmake_minimum_required(VERSION 3.15)

project(st-lib)
set(DRIVER Drivers/STM32L4xx_HAL_Driver/Src)
add_library(stlib
    STATIC
    ${DRIVER}/stm32l4xx_ll_gpio.c
    ${DRIVER}/stm32l4xx_ll_utils.c
    )

target_include_directories(stlib
    PUBLIC
    Drivers/STM32L4xx_HAL_Driver/Inc
    Drivers/CMSIS/Device/ST/STM32L4xx/Include
    Drivers/CMSIS/Include
    )

target_compile_definitions(stlib
    PUBLIC
    STM32L452xx=1
    USE_FULL_LL_DRIVER=1
    )

target_compile_options(stlib PRIVATE
        -march=armv7e-m
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -fdata-sections
        -ffunction-sections
        -Wall
        -fmessage-length=0
        $<$<CONFIG:Debug>:-Og>
        )
