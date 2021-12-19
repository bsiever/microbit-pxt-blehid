#ifndef HID_KEYBOARD_SERVICE_H
#define HID_KEYBOARD_SERVICE_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

class  BLEMouseService : public HIDService {
    public:

    /**
     * Constructor.
     * Create a representation of the Bluetooth Mouse Service
     * @param _ble The instance of a BLE device that we're running on.
     */
    BLEMouseService( BLEDevice &_ble);
    void send(uint8_t dx, uint8_t dy, bool left, bool middle, bool right, uint8_t dscroll);
};
#endif
#endif 