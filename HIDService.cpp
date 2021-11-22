
#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"
#include "debug.h"

const uint16_t HIDService::charUUID[ mbbs_cIdxCOUNT] = { 0x2a19 };



/**
 * Constructor.
 * Create a representation of the Bluetooth SIG Battery Service
 * @param _ble The instance of a BLE device that we're running on.
 */
HIDService::HIDService( BLEDevice &_ble) : batteryLevel(100) {
        DEBUG("Batt. Serv starting\n");

    // Register the base UUID and create the service.
    bs_uuid_type = BLE_UUID_TYPE_BLE;  // Set the UUID type to 0x01, which should be Bluetooth SIG ID
    uint16_t serviceUUID = 0x1812;  // HID Service: 0x1812  (Set off for a bit to test / prevent iOS scarf of service)
    CreateService( serviceUUID);
    
    // Create the data structures that represent each of our characteristics in Soft Device.
    CreateCharacteristic( mbbs_cIdxLEVEL, charUUID[ mbbs_cIdxLEVEL],
                        (uint8_t *)&batteryLevel,
                        sizeof(batteryLevel), sizeof(batteryLevel),
                        microbit_propREAD | microbit_propNOTIFY);
}

void HIDService::setLevel(uint8_t newLevel)
{
    batteryLevel = newLevel; 
    notifyChrValue( mbbs_cIdxLEVEL, (uint8_t *)&batteryLevel, sizeof(batteryLevel)); 
}



/**
  * Invoked when BLE connects.
  */
void HIDService::onConnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("Batt. Serv onConnect\n");
}


/**
  * Invoked when BLE disconnects.
  */
void HIDService::onDisconnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("Batt. Serv onDisconnect\n");
}


/**
  * Callback. Invoked when any of our attributes are written via BLE.
  */
void HIDService::onDataWritten( const microbit_ble_evt_write_t *params)
{
    DEBUG("Batt. Serv onDataWritten\n");
}



#endif