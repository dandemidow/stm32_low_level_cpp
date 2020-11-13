# stm32l4_low_level_cpp

This project is just a fantasy of how the ST low-level library can be implemented in pure C++. 
The LED blinking project was taken as an example. The main aim is to use the C++ techniques for critical places with minimum memory consumption.
Memory-mapped objects replaced the device registers structure, the free functions from the ll namespace replaced low-level library functions.
The C++ startup file also replaced the assembler file.
