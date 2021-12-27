#ifndef HID_GAMEPAD_REPORTER_H
#define HID_GAMEPAD_REPORTER_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

class  GamepadReporter : public HIDReporter {
    public:
    static GamepadReporter* getInstance();
    
    void send(uint16_t buttons, uint8_t x, uint8_t y, uint8_t z, uint8_t rx);

    private: 
    GamepadReporter();
    static GamepadReporter *reporter;

};
#endif
#endif 