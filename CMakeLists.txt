cmake_minimum_required(VERSION 3.15)

project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
enable_language(C ASM)

set(EXECUTABLE ${PROJECT_NAME}.elf)

#include(examples/nucleo-l452re/blinking_led/source.cmake)
include(${EXAMPLE_SOURCE_PATH}/source.cmake)

add_executable(${EXECUTABLE} ${SRCS})

target_link_options(${EXECUTABLE}
  PRIVATE
    ${COMMON_OPTS}
    -static
    -T${LINKER_SCRIPT}
    "-Wl,-Map=${PROJECT_NAME}.map,--cref"
    "-Wl,--gc-sections"
)

message("${CMAKE_CXX_COMPILER_TARGET}")

add_compile_definitions(${BOARD})
target_compile_options(${EXECUTABLE}
  PRIVATE
    "${ARCH}"
    "${COMMON_OPTS}"
)

add_subdirectory(ll)

target_link_libraries(${EXECUTABLE}
  PUBLIC
    stm32ll
)

add_custom_command(TARGET ${PROJECT_NAME}.elf
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)
