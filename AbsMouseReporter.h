#ifndef HID_MOUSE_REPORTER_H
#define HID_MOUSE_REPORTER_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

class  AbsoluteMouseReporter : public HIDReporter {
    public:
    static AbsoluteMouseReporter* getInstance();
    
    void send(uint16_t x, uint16_t y, bool left, bool middle, bool right);

    private: 
    AbsoluteMouseReporter();
    static AbsoluteMouseReporter *reporter;

};
#endif
#endif 