# stm32_low_level_cpp

This project is just a fantasy of how the ST low-level library can be implemented in pure C++.</br>
The LED blinking project was taken as a base example.</br>
I also will try to extend the example set for boards I have.</br>
The main aim is to use the C++ techniques for critical places with minimum memory consumption, although usability is also essential.</br>
Memory-mapped objects replaced the device registers structure, the free functions from the ll namespace replaced low-level library functions.
The C++ startup file also replaced the assembler file.</br>
The **C++20** standard is used.</br>

The examples are available for now: 
 - nucleo-l452re board:
   - blinking led
   - base timer
 - stm32f0308-discovery board:
   - blinking led
   - base timer
   
You can find it in the examples folder.</br>
For CMake build process the **EXAMPLE_SOURCE_PATH** option should be defined:</br>
_-DEXAMPLE_SOURCE_PATH:FILEPATH=C:/stm32llcpp20/examples/nucleo-l452re/blinking_led_

The complete command ex.:
```
C:\cygwin64\bin\cmake.exe C:/cygwin64/home/dan/stm32llcpp20 -GNinja "-DCMAKE_BUILD_TYPE:STRING=Debug" "-DCMAKE_CXX_COMPILER:STRING=C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q2-preview/bin/arm-none-eabi-g++.exe" "-DCMAKE_CXX_COMPILER_TARGET :STRING=arm-none-eabi" "-DCMAKE_C_COMPILER:STRING=C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q2-preview/bin/arm-none-eabi-gcc-10.1.1.exe" "-DCMAKE_C_COMPILER_TARGET:STRING=arm-none-eabi" "-DCMAKE_MAKE_PROGRAM:FILEPATH=C:/cygwin64/bin/ninja.exe" "-DCMAKE_PREFIX_PATH:STRING=" "-DCMAKE_SYSROOT:STRING=C:/Program Files (x86)/GNU Tools Arm Embedded/9 2019-q4-major/arm-none-eabi" "-DCMAKE_TOOLCHAIN_FILE:INTERNAL=toolchain-gcc.cmake" "-DEXAMPLE_SOURCE_PATH:FILEPATH=C:/cygwin64/home/dan/stm32llcpp20/examples/nucleo-l452re/blinking_led"
```

The c++ can be useful when we talk about code size. And I can show my measurement of the firmware size. </br>
The first one is the moment when I just started the c code replacement. The last one is the final commit, which removed all c code. </br>
The blinking led FW (stm32l4 board) size changes
```
2020-10-28:
   text    data     bss     dec     hex filename
   1264     432    1568    3264     cc0 build/st_ll_app.elf
```
```   
2020-11-15 (without ST Cube generated code):
   text    data     bss     dec     hex filename
   1120     432    1568    3120     c30 build/st_ll_app.elf
```
```
2020-12-23:
   text    data     bss     dec     hex filename
   1040     432    1568    3040     be0 build/st_ll_app.elf
```

The GCC compiler version:</br>
``` 
 arm-none-eabi-g++ -v
Using built-in specs.
COLLECT_GCC=C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2020-q2-preview\bin\arm-none-eabi-g++.exe
COLLECT_LTO_WRAPPER=c:/program\ files\ (x86)/gnu\ arm\ embedded\ toolchain/10\ 2020-q2-preview/bin/../lib/gcc/arm-none-eabi/10.1.1/lto-wrapper.exe
Target: arm-none-eabi
Configured with: /mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/src/gcc/configure --build=x86_64-linux-gnu --host=i686-w64-mingw32 --target=arm-none-eabi --prefix=/mnt/w
orkspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/install-mingw --libexecdir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/install-mingw
/lib --infodir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/install-mingw/share/doc/gcc-arm-none-eabi/info --mandir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GC
C-10-pipeline-13_20200625_1593044217/install-mingw/share/doc/gcc-arm-none-eabi/man --htmldir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/install-mingw/share/doc/gcc-a
rm-none-eabi/html --pdfdir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/install-mingw/share/doc/gcc-arm-none-eabi/pdf --enable-languages=c,c++ --enable-mingw-wildcard
--disable-decimal-float --disable-libffi --disable-libgomp --disable-libmudflap --disable-libquadmath --disable-libssp --disable-libstdcxx-pch --disable-nls --disable-shared --disable-threads --disable-tls --wi
th-gnu-as --with-gnu-ld --with-headers=yes --with-newlib --with-python-dir=share/gcc-arm-none-eabi --with-sysroot=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/install-
mingw/arm-none-eabi --with-libiconv-prefix=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/build-mingw/host-libs/usr --with-gmp=/mnt/workspace/workspace/GCC-10-pipeline/j
enkins-GCC-10-pipeline-13_20200625_1593044217/build-mingw/host-libs/usr --with-mpfr=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/build-mingw/host-libs/usr --with-mpc=/
mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/build-mingw/host-libs/usr --with-isl=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_159304421
7/build-mingw/host-libs/usr --with-libelf=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-13_20200625_1593044217/build-mingw/host-libs/usr --with-host-libstdcxx='-static-libgcc -Wl,-Bstatic,-ls
tdc++,-Bdynamic -lm' --with-pkgversion='GNU Arm Embedded Toolchain 10-2020-q2-preview' --with-multilib-list=rmprofile,aprofile
Thread model: single
Supported LTO compression algorithms: zlib
gcc version 10.1.1 20200529 (release) (GNU Arm Embedded Toolchain 10-2020-q2-preview)
```

