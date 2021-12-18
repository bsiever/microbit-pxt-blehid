#include"ascii2scan.h"

// Convert an ASCII character from [0x20-0x7e] (space to ~) a HID scancode)
// Upper byte of return value indicats if shift is needed (a 0x00=>No, 0x01=>Yes)
// Lower byte is the scan code to return
// 0x0000 => No valid scan code 

// Based on https://usb.org/sites/default/files/hut1_21.pdf chapter 10, page 82
uint16_t ascii2scan(char c) {
    bool shift = false;
    uint8_t code = 0x00;

    if(c<0x20) { 
        // Before space / ' '...Nothing
    } else 
    if(c<0x30) {  // Space up <= '0'
        const uint8_t codes[] = 
                // SPACE !     "     #     $     %     &     '      (     )     *     +      ,       -      .      /
                { 0x2c,  0x1e, 0x34, 0x20, 0x21, 0x22, 0x24, 0x34,  0x26, 0x27, 0x25, 0x2e,  0x36,   0x2d,  0x37,  0x38};
        const bool shifts[] = 
                {false,  true, true, true, true, true, true, false, true, true, true, true, false,   false, false, false}; 
        uint8_t index = c-0x20;
        shift = shifts[index];
        code = codes[index];
    } else 
    if(c<0x3a) {  // [0..9]
        if(c=='0')  // 0x30
            code = 0x27;
        else 
            code = 0x1e + (c-'1');  // 1-9
    } else
    if(c<0x41) {  // 9<c<A
        const uint8_t codes[] = 
                // :     ;     <     =      >     ?     @
                { 0x33,  0x33, 0x36, 0x2e,  0x37, 0x38, 0x1f};
        const bool shifts[] = 
                {true,  false, true, false, true, true, true}; 
        uint8_t index = c-':';
        shift = shifts[index];
        code = codes[index];
    } else 
    if(c<0x5B) {  // [A..Z]
        shift = true;
        code = 0x04 + c-'A';

    } else 
    if(c<0x61) { // Before 'a'
        const uint8_t codes[] = 
                // [     \      ]      ^     _     `
                { 0x2f,  0x31,  0x30,  0x23, 0x2D, 0x35};
        const bool shifts[] = 
                {false,  false, false, true, true, false}; 
        uint8_t index = c-'[';
        shift = shifts[index];
        code = codes[index];
    } else 
    if(c<0x7b) {  // [a..z]
        code = 0x04 + c-'a';
    } else
    if(c<0x7f) {  // Before del
        const uint8_t codes[] = 
                // {     |     }     ~
                { 0x2f,  0x31, 0x30, 0x35};
        const bool shifts[] = 
                {true,  true,  true, true}; 
        uint8_t index = c-'{';
        shift = shifts[index];
        code = codes[index];
    }
    return (shift ? 0x0100 : 0x0000) | code;
}