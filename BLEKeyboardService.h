#ifndef HID_KEYBOARD_SERVICE_H
#define HID_KEYBOARD_SERVICE_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

class  BLEKeyboardService : public HIDService {
    public:

    /**
     * Constructor.
     * Create a representation of the Bluetooth SIG Keyboard Service
     * @param _ble The instance of a BLE device that we're running on.
     */
    BLEKeyboardService( BLEDevice &_ble);
    void sendScanCode(uint8_t c, uint8_t modifiers);
    void sendString(char *str, int len);
    void sendSimultaneousKeys(char *str, int len);

    private: 
    const int betweenKeyDelay = 40; 

};

#endif
#endif 