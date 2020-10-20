import qbs

Project {
CppApplication {
    Depends { name: "st_ll" }
    cpp.compilerIncludePaths:[""]
    cpp.compilerFrameworkPaths:[""]
    cpp.compilerLibraryPaths:[""]

    files: ["*.c", "*.s", "*.cmake", "CMakeLists.txt"]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}

StaticLibrary {
    cpp.compilerIncludePaths:[""]
    cpp.compilerFrameworkPaths:[""]
    cpp.compilerLibraryPaths:[""]
    name: "st_ll"
    Depends { name: "cpp" }

    files: ["STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Src/*.c"]

    cpp.includePaths: [
        "STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Inc",
        "STM32CubeL4/Drivers/CMSIS/Device/ST/STM32L4xx/Include"
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [
            "STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Inc",
            "STM32CubeL4/Drivers/CMSIS/Device/ST/STM32L4xx/Include",
            "STM32CubeL4/Drivers/CMSIS/Include"
        ]
        cpp.defines: ["STM32L452xx", "USE_FULL_LL_DRIVER"]
    }
}

}
