
#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "BatteryService.h"
#include "debug.h"
/**
 * Constructor.
 * Create a representation of the Bluetooth SIG Battery Service
 * @param _ble The instance of a BLE device that we're running on.
 */
BatteryService::BatteryService( BLEDevice &_ble) {
    // Register the base UUID and create the service.
    bs_uuid_type = BLE_UUID_TYPE_BLE;  // Set the UUID type to 0x01, which should be Bluetooth SIG ID
    uint16_t serviceUUID = 0x180f;  // Battery Service
    CreateService( serviceUUID);
    
    // // Create the data structures that represent each of our characteristics in Soft Device.
    // CreateCharacteristic( mbbs_cIdxDATA, charUUID[ mbbs_cIdxDATA],
    //                     (uint8_t *)accelerometerDataCharacteristicBuffer,
    //                     sizeof(accelerometerDataCharacteristicBuffer), sizeof(accelerometerDataCharacteristicBuffer),
    //                     microbit_propREAD | microbit_propNOTIFY);

    // CreateCharacteristic( mbbs_cIdxPERIOD, charUUID[ mbbs_cIdxPERIOD],
    //                     (uint8_t *)&accelerometerPeriodCharacteristicBuffer,
    //                     sizeof(accelerometerPeriodCharacteristicBuffer), sizeof(accelerometerPeriodCharacteristicBuffer),
    //      
}


/**
  * Invoked when BLE connects.
  */
void BatteryService::onConnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("Batt. Serv onConnect");
}


/**
  * Invoked when BLE disconnects.
  */
void BatteryService::onDisconnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("Batt. Serv onDisconnect");
}


/**
  * Callback. Invoked when any of our attributes are written via BLE.
  */
void BatteryService::onDataWritten( const microbit_ble_evt_write_t *params)
{
    DEBUG("Batt. Serv onDataWritten");

}



#endif