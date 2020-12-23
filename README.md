# stm32l4_low_level_cpp

This project is just a fantasy of how the ST low-level library can be implemented in pure C++.</br>
The LED blinking project was taken as an example.</br>
The main aim is to use the C++ techniques for critical places with minimum memory consumption.</br>
Memory-mapped objects replaced the device registers structure, the free functions from the ll namespace replaced low-level library functions.
The C++ startup file also replaced the assembler file.</br>
The **C++20** standard is used.</br>

The FW size changes
```
2020-10-28:
arm-none-eabi-size.exe st_ll_app.elf
   text    data     bss     dec     hex filename
   1264     432    1568    3264     cc0 build/st_ll_app.elf
```
```   
2020-11-15 (without ST Cube generated code):
arm-none-eabi-size.exe st_ll_app.elf
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

