cmake_minimum_required(VERSION 3.15)

project(st_ll_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
enable_language(C ASM)

set(SRCS
        main.cpp
        stm32l4xx_it.cpp
        system_stm32l4xx.cpp
        startup.cpp)

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_subdirectory(STM32CubeL4)

add_executable(${EXECUTABLE} ${SRCS})

target_link_libraries(${EXECUTABLE}
    PUBLIC
    stlib
    )

target_include_directories(${EXECUTABLE} PRIVATE
        BSP/Inc
        BSP/Drivers/STM32F4xx_HAL_Driver/Inc
        BSP/Drivers/CMSIS/Device/ST/STM32F4xx/Include
        BSP/Drivers/CMSIS/Include
        )

target_compile_options(${EXECUTABLE} PRIVATE
        -march=armv7e-m
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -fdata-sections
        -ffunction-sections
        -Wall
        -Wextra
        -fmessage-length=0
        -fno-exceptions
        -fno-rtti
        $<$<CONFIG:Debug>:-Og>
        )

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32L452RETx_FLASH.ld")

target_link_options(${EXECUTABLE} PRIVATE
        -static
        -T${LINKER_SCRIPT}
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -specs=nano.specs
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        )

add_custom_command(TARGET ${PROJECT_NAME}.elf
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
