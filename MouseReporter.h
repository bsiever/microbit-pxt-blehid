#ifndef HID_MOUSE_REPORTER_H
#define HID_MOUSE_REPORTER_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

class  MouseReporter : public HIDReporter {
    public:
    static MouseReporter* getInstance();
    
    void send(uint8_t dx, uint8_t dy, bool left, bool middle, bool right, uint8_t dscroll);

    private: 
    MouseReporter();
    static MouseReporter *reporter;

};
#endif
#endif 