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

add_executable(${EXECUTABLE} ${SRCS})

target_compile_options(${EXECUTABLE}
  PRIVATE
    $<$<CONFIG:Debug>:-Og>
)

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32L452RETx_FLASH.ld")

target_link_options(${EXECUTABLE} PRIVATE
        -static
        -T${LINKER_SCRIPT}
        )

target_compile_definitions(${EXECUTABLE}
  PUBLIC
    STM32L452
)

add_subdirectory(ll)

target_link_libraries(${EXECUTABLE}
  PUBLIC
    stll
)

add_custom_command(TARGET ${PROJECT_NAME}.elf
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
