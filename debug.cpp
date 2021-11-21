
#include "debug.h"

#ifdef DEBUG_ENABLED

#include "pxt.h"
#include "MicroBit.h"
    /**
     * 
     */
// https://www.forward.com.au/pfod/microbit/gettingStarted.html
void loopUntilSent(ManagedString str) {
    int rtn = uBit.serial.send(str);
    while(rtn == MICROBIT_SERIAL_IN_USE) {
       uBit.sleep(0); // let other tasks run
       rtn = uBit.serial.send(str); 
    }
}

void loopUntilSent(int str) {
    int rtn = uBit.serial.send(str);
    while(rtn == MICROBIT_SERIAL_IN_USE) {
       uBit.sleep(0); // let other tasks run
       rtn = uBit.serial.send(str); 
    }
}
#endif 
