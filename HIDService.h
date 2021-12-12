#ifndef HID_SERVICE_H
#define HID_SERVICE_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "MicroBitBLEManager.h"
#include "MicroBitBLEService.h"
#include "EventModel.h"
#include "debug.h"


/**
  * Class definition for a MicroBit BLE Accelerometer Service.
  * Provides access to live accelerometer data via Bluetooth, and provides basic configuration options.
  */
class HIDService : public MicroBitBLEService
{
    public:
    /**
     * Constructor.
     * Create a representation of the Bluetooth SIG Battery Service
     * @param _ble The instance of a BLE device that we're running on.
     */
    HIDService( BLEDevice &_ble);

    enum KeyModifiers {
      leftControlMask = 0x01,
      leftShiftMask = 0x02,
      leftAltMask = 0x04,
      leftGUIMask = 0x08,
      rightControlMask = 0x10,
      rightShiftMask = 0x20,
      rightAltMask = 0x40,
      rightGUIMask = 0x80
    };


    private:
    /**
      * Invoked when BLE connects.
      */
    void onConnect( const microbit_ble_evt_t *p_ble_evt);

    /**
      * Invoked when BLE disconnects.
      */
    void onDisconnect( const microbit_ble_evt_t *p_ble_evt);

    /**
      * Callback. Invoked when any of our attributes are written via BLE.
      */
    void onDataWritten( const microbit_ble_evt_write_t *params);


    /**
     * Callback. Invoked when any of our attributes are read via BLE.
     */
    void onDataRead( microbit_onDataRead_t *params);


    /*
    */
    void addReportDescriptor(uint16_t value_handle, uint8_t reportID, uint8_t reportTypeD);

    /*
    */
   void setKeyboardEnabled(bool status);


    // Debugging: Print the attribute / info.
    void debugAttribute(int index); 
    const int betweenKeyDelay = 40; 

    // Actual service data
    uint8_t protocolMode;  // 0=>Boot Protocol; 1=>Report
    static  uint16_t HIDInfo[];
    static  uint8_t reportMap[];
    uint8_t report[8];
    bool keyboardEnabled;
    // Index for each characteristic in arrays of handles and UUIDs
    typedef enum mbbs_cIdx
    {
        mbbs_cIdxProtocolMode,
        mbbs_cIdxHIDInfo,
        mbbs_cIdxReportMap,
        mbbs_cIdxReport,
        mbbs_cIdxCOUNT
    } mbbs_cIdx;

    // UUIDs for our service and characteristics
    static const uint16_t serviceUUID;
    static const uint16_t charUUID[ mbbs_cIdxCOUNT];
    
    // Data for each characteristic when they are held by Soft Device.
    MicroBitBLEChar      chars[ mbbs_cIdxCOUNT];



    public:
    
    int              characteristicCount()          { return mbbs_cIdxCOUNT; };
    MicroBitBLEChar *characteristicPtr( int idx)    { return &chars[ idx]; };

    void sendScanCode(uint8_t c, uint8_t modifiers);
    void sendString(char *str, int len);
    bool keyboardIsEnabled(); 

    static Action statusChangeHandler;

};

#endif
#endif