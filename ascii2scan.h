#ifndef ASCII2SCAN 
#define ASCII2SCAN

#include "pxt.h"

// Convert an ASCII character from [0x20-0x7e] (space to ~) a HID scancode)
// Upper byte of return value indicats if shift is needed (a 0x00=>No, 0x01=>Yes)
// Lower byte is the scan code to return
// 0x0000 => No valid scan code 
uint16_t ascii2scan(char c); 

#endif