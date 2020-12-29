
set(BOARD "STM32F030x8")
set(ARCH "-march=armv6-m")
set(COMMON_OPTS
    "-mcpu=cortex-m0"
    "-mthumb"
    "-mfloat-abi=soft"
)

set(SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(SRCS
    ${SOURCE_PATH}/main.cpp
    ${SOURCE_PATH}/stm32f0xx_it.cpp
    ${SOURCE_PATH}/system_stm32f0xx.cpp
    ${SOURCE_PATH}/startup.cpp
)

set(LINKER_SCRIPT "${SOURCE_PATH}/STM32F030R8Tx_FLASH.ld")
