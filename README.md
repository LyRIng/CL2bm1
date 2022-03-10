## CL2bm1 CPU Board
(Original version 2012 - updated 03.2022)

### Introduction
This board contains an ATMega1284P controller, and has been active and in use since 2010 [CL2bm1-AVR](https://www.lyr-ing.com/Embedded/LyRAVR_CyEn.htm). Board CL2bm1 has been historically programmed with CodevisionAVR C compilers v3 or newer [ref-CVAVR,2022] but although it is not strictly Arduino-hardware compatible it can use many Arduino-AVR libraries and can be programmed with C++ style Arduino IDE [ref-ArduinoIDE,2021] and also with Visual Studio Code [ref-VSC,2022] with PlatformIO[ref-PIO,2022], both using GNU avr-gcc [ref-AVRgcc,2021] compilers. 
In directory **/schem** the complete schematic of the board is available.  


In the **/features** directory a description PDF of the board is available.  

### Programming Examples
Source code for programming examples is available in the **/examples** directory. 

### References

[Ref1 - LyR AVR+Cypress](https://www.lyr-ing.com/Embedded/LyRAVR_CyEn.htm)

[ref-CVAVR,2022] HP InfoTech / Codevision AVR C Compiler http://www.hpinfotech.ro/cvavr-features.html

[ref-ArduinoIDE,2021] Arduino IDE https://www.arduino.cc/en/software

[ref-VSC,2022] Microsoft Visual Studio Code https://code.visualstudio.com/

[ref-PIO,2022] Platform IO https://platformio.org/

ref-AVRgcc,2021] AVR GCC compiler: from https://blog.zakkemble.net/avr-gcc-builds/ 

