cmake_minimum_required(VERSION 3.15)

project(blinking_led LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
enable_language(C ASM)

set(EXECUTABLE ${PROJECT_NAME}.elf)

set(SRCS
    main.cpp
    stm32l4xx_it.cpp
    system_stm32l4xx.cpp
    startup.cpp
)

set(BOARD "STM32L452")
set(ARCH "-march=armv7e-m")
set(COMMON_OPTS
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
)
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32L452RETx_FLASH.ld")

add_executable(${EXECUTABLE} ${SRCS})

target_compile_options(${EXECUTABLE}
  PRIVATE
    $<$<CONFIG:Debug>:-Og>
)

target_link_options(${EXECUTABLE}
  PRIVATE
    -static
    -T${LINKER_SCRIPT}
)

add_compile_definitions(${BOARD})
add_compile_options("${ARCH}" "${COMMON_OPTS}")
add_link_options(${COMMON_OPTS})

add_subdirectory(ll)

target_link_libraries(${EXECUTABLE}
  PUBLIC
    stm32ll
)

add_custom_command(TARGET ${PROJECT_NAME}.elf
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
