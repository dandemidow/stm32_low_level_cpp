
set(BOARD "STM32L452")
set(ARCH "-march=armv7e-m")
set(COMMON_OPTS
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
)

set(SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(SRCS
    ${SOURCE_PATH}/main.cpp
    ${SOURCE_PATH}/stm32l4xx_it.cpp
    ${SOURCE_PATH}/system_stm32l4xx.cpp
    ${SOURCE_PATH}/startup.cpp
)

set(LINKER_SCRIPT "${SOURCE_PATH}/STM32L452RETx_FLASH.ld")
