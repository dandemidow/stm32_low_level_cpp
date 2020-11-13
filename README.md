# stm32l4_low_level_cpp

This project is just a fantasy of how the ST low-level library can be implemented in pure C++.</br>
The LED blinking project was taken as an example.</br>
The main aim is to use the C++ techniques for critical places with minimum memory consumption.</br>
Memory-mapped objects replaced the device registers structure, the free functions from the ll namespace replaced low-level library functions.
The C++ startup file also replaced the assembler file.
