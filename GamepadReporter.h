#ifndef HID_GAMEPAD_REPORTER_H
#define HID_GAMEPAD_REPORTER_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

class  GamepadReporter : public HIDReporter {
    public:
    static GamepadReporter* getInstance();
    
    // D-Pad bits:  0000 Up Down Right Left
    void send(uint16_t buttons, uint8_t x, uint8_t y, uint8_t rx, uint8_t ry, uint8_t dpad);

    private: 
    GamepadReporter();
    static GamepadReporter *reporter;

};
#endif
#endif 