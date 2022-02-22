#ifndef HID_SERVICE_H
#define HID_SERVICE_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "MicroBitBLEManager.h"
#include "MicroBitBLEService.h"
#include "EventModel.h"
#include "debug.h"

#include "HIDReporter.h"
#include"peer_manager.h"


/*
| Reporter | Map Size | Report Size |
|:--------:|:--------:|:-----------:|
| Keyboard |     47   |       8     |
| Mouse    |     54   |       4     |
| Abs Mouse|     54   |       5     |
| Media    |     37   |       1     |
| Gamepad  |     64   |       7     |
|          |          |             |
|Total/Max |   249    |       8     |
*/

const int numReportsMax = 4;
const int reportMapMaxSize = 200;  // 172 is enough for any 3
const int reportMaxSize = 8;       // Max size  
const int minTimeBetweenNotifies = 30;  // Minimum amount of time between sending notifies

/**
  * Class definition for a MicroBit BLE HID Service.
  */
class HIDService : public MicroBitBLEService
{
  public:
    static HIDService *getInstance();

  private:
    static HIDService *service; // Singleton
    friend class HIDReporter;

    int addHIDReporter(HIDReporter& reporter);
    
    void setName();

    /**
     * Constructor.
     * Create a representation of the Bluetooth SIG HID Service
     * @param _ble The instance of a BLE device that we're running on.
     */
    HIDService();

    /**
      * Invoked when BLE connects.
      */
    void onConnect(const microbit_ble_evt_t *p_ble_evt);

    /**
      * Invoked when BLE disconnects.
      */
    void onDisconnect(const microbit_ble_evt_t *p_ble_evt);

    /**
      * Callback. Invoked when any of our attributes are written via BLE.
      */
    void onDataWritten(const microbit_ble_evt_write_t *params);

    /**
     * Callback. Invoked when any of our attributes are read via BLE.
     */
    void onDataRead(microbit_onDataRead_t *params);

    // BLE Events...Let's monitor 'em all. 
    bool onBleEvent(const microbit_ble_evt_t *p_ble_evt);

    // Override notification process to enforce minimum time between events. 
    bool notifyChrValue( int idx, const uint8_t *data, uint16_t length);

    // Peer Manager Events (re-enable CCCDs)
    void pm_events( const pm_evt_t* p_event);

    // Static instance variables were created to facilitate multiple HID Services
    // (Now a singleton is used and they could be converted to instance variables)

    // Peer Manager Events (re-enable CCCDs)
    static void static_pm_events( const pm_evt_t* p_event);

    // Index for each characteristic in arrays of handles and UUIDs
    typedef enum mbbs_cIdx
    {
        mbbs_cIdxProtocolMode,
        mbbs_cIdxHIDInfo,
        mbbs_cIdxReportMap,
        mbbs_cIdxReport1,
        mbbs_cIdxReport2,
        mbbs_cIdxReport3,
        mbbs_cIdxReport4,  // NOTE: Adding Reports requires updating chars array in HIDService.cpp
                           //       and const numReports to be changed
        mbbs_cIdxCOUNT
    } mbbs_cIdx;

    // Service UUID
    static const uint16_t hidService;

    // UUIDs for our service and characteristics
    static const uint16_t charUUID[mbbs_cIdxCOUNT];
    
    static const int EVT_STATUS;  // Reporters send it via MicroBitEvent()

    // Data for each characteristic when they are held by Soft Device.
    MicroBitBLEChar      chars[mbbs_cIdxCOUNT];

    int              characteristicCount()          { return mbbs_cIdxCOUNT; };
    MicroBitBLEChar *characteristicPtr(int idx)     { return &chars[ idx]; };

    // HID Info characteristic
    // Can't be const (may be modified by stack; should be persistent)
    static uint16_t HIDInfo[2];

    // Can't be const (may be modified by stack; should be persistent)
    uint8_t protocolMode;  // 0=>Boot Protocol; 1=>Report; Always 1 

    // Actual service data 
    uint8_t reportMap[reportMapMaxSize];
    unsigned reportMapUsed;

    uint8_t   reports[numReportsMax][reportMaxSize];
    HIDReporter *reporters[numReportsMax];
    unsigned    numReporters; 
    
    char gapName[14];

    void addReporter(HIDReporter *reporter);
    uint8_t *getReportBuffer(int index) { return reports[index]; }

    void addReportDescriptor(uint16_t value_handle, uint8_t reportID, uint8_t reportTypeD);

    void advertiseHID();

    // Debugging: Print the attribute / info.
    void debugAttribute(int index); 
};
#endif
#endif