
#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"
#include "debug.h"

#define HID_TESTING 1

const uint16_t HIDService::serviceUUID = 0x1812;   // 0x1812 = HID 

const uint16_t HIDService::charUUID[ mbbs_cIdxCOUNT ] = { 
#ifdef HID_TESTING
  0x2A4E,  //  ProtocolMode
  0x8A4A,  //  HIDInfo    0x2A4A
  0x8A4B   // Report Map
#else
  0x2A4E,  //  ProtocolMode
  0x2A4A,  //  HIDInfo (Confirm Value without BLUETOOTH_PRIVLEDGED exception)   0x2A4A
  0x2A4B   // Report Map
#endif
};

uint16_t HIDService::HIDInfo[] = { 
  0x0111,
  0x0002
};

// Copied from https://docs.silabs.com/bluetooth/2.13/code-examples/applications/ble-hid-keyboard
uint8_t HIDService::reportMap[] =
{
0x05, 0x01, //	Usage Page (Generic Desktop)
0x09, 0x06, //	Usage (Keyboard)
0xa1, 0x01, //	Collection (Application)
0x05, 0x07, //	Usage Page (Keyboard)
0x19, 0xe0, //	Usage Minimum (Keyboard LeftControl)
0x29, 0xe7, //	Usage Maximum (Keyboard Right GUI)
0x15, 0x00, //	Logical Minimum (0)
0x25, 0x01, //	Logical Maximum (1)
0x75, 0x01, //	Report Size (1)
0x95, 0x08, //	Report Count (8)
0x81, 0x02, //	Input (Data, Variable, Absolute) Modifier byte
0x95, 0x01, //	Report Count (1)
0x75, 0x08, //	Report Size (8)
0x81, 0x01, //	Input (Constant) Reserved byte
0x95, 0x06, //	Report Count (6)
0x75, 0x08, //	Report Size (8)
0x15, 0x00, //	Logical Minimum (0)
0x25, 0x65, //	Logical Maximum (101)
0x05, 0x07, //	Usage Page (Key Codes)
0x05, 0x01, //	Usage Minimum (Reserved (no event indicated))
0x05, 0x01, //	Usage Maximum (Keyboard Application)
0x05, 0x01, //	Input (Data,Array) Key arrays (6 bytes)
0xc0,       //	End Collection
};


/**
 * Constructor.
 * Create a representation of the Bluetooth SIG Battery Service
 * @param _ble The instance of a BLE device that we're running on.
 */
HIDService::HIDService( BLEDevice &_ble) 
    : protocolMode(0x00) // 0x01 = Report Protocol
{
        DEBUG("HID. Serv starting\n");

    // Register the base UUID and create the service.
    bs_uuid_type = BLE_UUID_TYPE_BLE;  // Set the UUID type to 0x01, which should be Bluetooth SIG ID
    CreateService( serviceUUID);
    
    // Create the data structures that represent each of our characteristics in Soft Device.
    CreateCharacteristic( mbbs_cIdxProtocolMode, charUUID[ mbbs_cIdxProtocolMode ],
                        (uint8_t *)&protocolMode,
                        sizeof(protocolMode), sizeof(protocolMode),
                        microbit_propREAD | microbit_propWRITE_WITHOUT);

    CreateCharacteristic( mbbs_cIdxHIDInfo, charUUID[ mbbs_cIdxHIDInfo ],
                        (uint8_t *)HIDInfo,
                        //sizeof(HIDInfo), sizeof(HIDInfo),
                        4,4,
                        microbit_propREAD  | microbit_propWRITE_WITHOUT);

    CreateCharacteristic( mbbs_cIdxReportMap, charUUID[ mbbs_cIdxReportMap ],
                        (uint8_t *)reportMap,
                        sizeof(reportMap), sizeof(reportMap),
                        microbit_propREAD );


}

// void HIDService::setLevel(uint8_t newLevel)
// {
//     batteryLevel = newLevel; 
//     notifyChrValue( mbbs_cIdxLEVEL, (uint8_t *)&batteryLevel, sizeof(batteryLevel)); 
// }



/**
  * Invoked when BLE connects.
  */
void HIDService::onConnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("HID. Serv onConnect\n");
}


/**
  * Invoked when BLE disconnects.
  */
void HIDService::onDisconnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("HID. Serv onDisconnect\n");
}


/**
  * Callback. Invoked when any of our attributes are written via BLE.
  */
void HIDService::onDataWritten( const microbit_ble_evt_write_t *params)
{
    DEBUG("HID. Serv onDataWritten\n");
    if(params->handle == valueHandle(mbbs_cIdxProtocolMode)) {
      DEBUG("HID: Data to Protocol");
      protocolMode = params->data[0];
      // 0=>Boot Protocol; 1->Enumeration; ...2.255 ???

      // params->data and params->len
      setChrValue( mbbs_cIdxProtocolMode, (const uint8_t *)&protocolMode, sizeof(protocolMode));

    }
}



#endif