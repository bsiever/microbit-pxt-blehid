#ifndef DEBUG_DISP 
#define DEBUG_DISP

#define DEBUG_ENABLED 1

#ifdef DEBUG_ENABLED 

#include "pxt.h"
#include "MicroBit.h"

#define DEBUG(...) uBit.serial.printf( __VA_ARGS__ )
//#define DEBUG(...) MICROBIT_DEBUG_DMESG( __VA_ARGS__ )

#else 
#define DEBUG(str) 
#endif

#endif