#ifndef HID_SERVICE_H
#define HID_SERVICE_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "MicroBitBLEManager.h"
#include "MicroBitBLEService.h"
#include "EventModel.h"
#include "debug.h"


/**
  * Class definition for a MicroBit BLE HID Service.
  */
class HIDService : public MicroBitBLEService
{
    protected:
    /**
     * Constructor.
     * Create a representation of the Bluetooth SIG HID Service
     * @param _ble The instance of a BLE device that we're running on.
     */
    HIDService( BLEDevice &_ble, 
                uint8_t *_reportMap, int _reportMapSize, 
                uint8_t *_report,    int _reportSize, 
                int _EVT_ID,
                const char *className) ;

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
    void setEnabled(bool status);


    // Actual service data (must be initialized by subclasses)
    // Things to initialize in the constructor
    const uint8_t *reportMap;
    const int reportMapSize;
    uint8_t *report;
    const int reportSize;


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
    static const uint16_t charUUID[mbbs_cIdxCOUNT];
    
    const int EVT_ID;
    // Data for each characteristic when they are held by Soft Device.
    MicroBitBLEChar      chars[ mbbs_cIdxCOUNT];


    int              characteristicCount()          { return mbbs_cIdxCOUNT; };
    MicroBitBLEChar *characteristicPtr( int idx)    { return &chars[ idx]; };
    Action statusChangeHandler;

    public:

    bool isEnabled() { return enabled; }
    /*
    */
    void setStatusChangeHandler(Action action);


  private:
      /*
    */
    void addReportDescriptor(uint16_t value_handle, uint8_t reportID, uint8_t reportTypeD);

    // Debugging: Print the attribute / info.
    void debugAttribute(int index); 

    static const uint16_t HIDInfo[2];

    static const int EVT_STATUS;
    static uint8_t   protocolMode;  // 0=>Boot Protocol; 1=>Report

    // Service data (managed by this class)
    bool enabled;

    static bool advertisingInitialized;
    const char *className;
    void advertiseHID();

};

#endif
#endif