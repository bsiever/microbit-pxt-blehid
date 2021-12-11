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
      leftControlMask = 0x80,
      leftShiftMask = 0x40,
      leftAltMask = 0x20,
      leftGUIMask = 0x10,
      rightControlMask = 0x08,
      rightShiftMask = 0x04,
      rightAltMask = 0x02,
      rightGUIMask = 0x01
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
    void addReportDescriptor(uint16_t value_handle, uint8_t reportID, uint8_t reportType);


#ifdef DEBUG_ENABLED
    // Debugging: Print the attribute / info.
    void debugAttribute(int index); 
#endif 

    // Actual service data
    uint8_t protocolMode;  // 0=>Boot Protocol; 1=>Report
    static  uint16_t HIDInfo[];
    static  const uint8_t reportMap[];
    uint8_t report[8];

    // Index for each charactersitic in arrays of handles and UUIDs
    typedef enum mbbs_cIdx
    {
        mbbs_cIdxProtocolMode,
        mbbs_cIdxHIDInfo,
        mbbs_cIdxReportMap,
        mbbs_cIdxReport,
      //  mbbs_cIdxBootKbdInp,
      //  mbbs_cIdxBootKbdOut,
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

    void sendScanCode(uint8_t c, uint8_t modifiers = 0);

};

#endif
#endif