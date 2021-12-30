#ifndef HID_KEYBOARD_REPORTER_H
#define HID_KEYBOARD_REPORTER_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDReporter.h"

class  KeyboardReporter : public HIDReporter {
public:
    static KeyboardReporter* getInstance();
    void sendScanCode(uint8_t c, uint8_t modifiers);
    void sendString(char *str, int len);
    void sendSimultaneousKeys(char *str, int len);

private: 
    KeyboardReporter();

private: 
    const int betweenKeyDelay = 40; 
    static KeyboardReporter *reporter;
};

#endif
#endif 