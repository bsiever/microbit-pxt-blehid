#ifndef HID_MOUSE_REPORTER_H
#define HID_MOUSE_REPORTER_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

class  AbsoluteMouseReporter : public HIDReporter {
    public:
    static AbsoluteMouseReporter* getInstance();
    
    void send(uint8_t x, uint8_t y, bool left, bool middle, bool right, uint8_t dscroll);

    private: 
    AbsoluteMouseReporter();
    static AbsoluteMouseReporter *reporter;

};
#endif
#endif 