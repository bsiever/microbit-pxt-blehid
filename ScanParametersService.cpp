
#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "ScanParametersService.h"
#include "debug.h"

// Service XML: https://www.bluetooth.com/wp-content/uploads/Sitecore-Media-Library/Gatt/Xml/Services/org.bluetooth.service.scan_parameters.xml
// Service PDF: https://www.bluetooth.com/specifications/specs/scan-parameters-service-1-0/
// UUIDs: https://btprodspecificationrefs.blob.core.windows.net/assigned-values/16-bit%20UUID%20Numbers%20Document.pdf

// 
const uint16_t ScanParametersService::charUUID[ mbbs_cIdxCOUNT] = { 
  0x2a4f  // Scan Interval Window
};

/**
 * Constructor.
 * Create a representation of the Bluetooth SIG Scan Parameters Service
 * @param _ble The instance of a BLE device that we're running on.
 */
ScanParametersService::ScanParametersService( BLEDevice &_ble) {
        DEBUG("Scan Prams. Serv starting\n");

    // Register the base UUID and create the service.
    bs_uuid_type = BLE_UUID_TYPE_BLE;  // Set the UUID type to 0x01, which should be Bluetooth SIG ID
    uint16_t serviceUUID = 0x1813;  // Scan Parameters Service
    CreateService( serviceUUID);
    
    // Create the data structures that represent each of our characteristics in Soft Device.
    CreateCharacteristic( mbbs_cIdxPARAMS, charUUID[ mbbs_cIdxPARAMS],
                        (uint8_t *)&scanParameters,
                        sizeof(scanParameters), sizeof(scanParameters),
                        microbit_propWRITE_WITHOUT);
}


/**
  * Invoked when BLE connects.
  */
void ScanParametersService::onConnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("Scan Params. Serv onConnect\n");
}


/**
  * Invoked when BLE disconnects.
  */
void ScanParametersService::onDisconnect( const microbit_ble_evt_t *p_ble_evt)
{
    DEBUG("Scan Params. Serv onDisconnect\n");
}


/**
  * Callback. Invoked when any of our attributes are written via BLE.
  */
void ScanParametersService::onDataWritten( const microbit_ble_evt_write_t *params)
{
    DEBUG("Scan Params. Serv onDataWritten\n");
    uint8_t *data = (uint8_t *)params->data;

    if (params->handle == valueHandle( mbbs_cIdxPARAMS) && params->len > 0 && params->len < 5)
    {
       // interrupt any animation that might be currently going on
      DEBUG("Wrote valid parameters\n");
    }
  }



#endif