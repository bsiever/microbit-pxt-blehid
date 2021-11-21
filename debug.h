#ifndef DEBUG_DISP 
#define DEBUG_DISP

#define DEBUG_ENABLED 1

#ifdef DEBUG_ENABLED 
#include "pxt.h"
#include "MicroBit.h"
void loopUntilSent(ManagedString str);
void loopUntilSent(int str);

#define DEBUG(str) loopUntilSent(str)

#else 
#define DEBUG(str) 
#endif

#endif