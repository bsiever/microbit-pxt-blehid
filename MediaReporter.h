#ifndef HID_MEDIA_REPORTER_H
#define HID_MEDIA_REPORTER_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDReporter.h"

class  MediaReporter : public HIDReporter {
    public:
    static MediaReporter* getInstance();
    void sendCode(uint8_t c);
    
    private: 
    MediaReporter();

    private: 
    static MediaReporter *reporter;
};
#endif
#endif 