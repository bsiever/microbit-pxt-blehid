
#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDService.h"

#include "ble_srv_common.h"
#include "ascii2scan.h"

//#define HID_TESTING 1
 

/**
 *  Keys:
 *     ASCII to Scancodes
 * 
 *     1. Single Bytes:  
 *           ASCII printable characters: [0x20-0X7E] represent that char
 *        
 *     2. Single byte 0x01-0x08: Control byte indicating which special key
 *        to apply (L Ctrl, L Shift, L Alt, LMeta, R Ctrl, R Shift, R Alt, R Meta) 
 *        These are all the "With" command that apply to the next character
 *          Shifts will not be supported / ignored (?) 
 *     
 *     3. Two byte command: 0x10 0xXX.  The 2nd byte is a literal key code to use
 *        (Copied directly to report)    
 * 
 *      ASCII           Scancode    + Shift
 *      Space   0x20      0x2C
 *      !       0x21      0x1e        TRUE      
 *      "       0x22     
 *      #       0x23
 *      $       0x24
 *      %       0x25
 *      &       0x26
 *      '       0x27
 *      (       0x28
 *      )       0x29
 *      *       0x2A
 *      -       0x2B
 *      .       0x2C
 *      /       0x2D
 *      )       0x2E
 *      /       0x2F  
 *      0       0x30      0x27
 *      1-9     0x31-39   0x1e-0x26
 *      :       0x3A
 *      ;       0x3B
 *      <       0x3C
 *      =       0x3D
 *      >       0x3E
 *      ?       0x3F
 *      :       0x3A
 *      @       0x40
 *      A-Z     0x41-0x5A   0x04-0x1dD  TRUE
 *      [       0x5B
 *      \       0x5C
 *      ]       0x5D
 *      ^       0x5E
 *      _       0x5F
 *      `       0x60
 *      a-z     0x61-0x7A   0x04-0x1dD
 *      {       0x7B
 *      |       0x7C
 *      }       0x7D
 *      ~       0x7E
 * 
 *  Non-printable:
 *    Escape, Delete, Return, Arrows, Tab, 
 *    F1-F12, Copy, Cut, Paste, 
 *    Mute, Vol up, Vol Down
 *      `       0x7F
 * 
 * */


/*
TODO / Major stuff:
  https://docs.silabs.com/bluetooth/2.13/code-examples/applications/ble-hid-keyboard

ASCII / typeable:
  A-Z,a-z,0-9 are programmatic
  Other typeables are lookup?
Non-typeables:
  "Modifiers"
  Enter, delete, arrows, F1-F12, Tab

OS Specific:
  Apple's Option = Windows Windows key?

Keyboard keys:
  A-Za-z,0-9,special chars (shift + 0-9, " ", F1-F12, arrows)
  enter/return/delete/escape
Keypad keys:
  numbers, arrows, 
Modifiers:
   Left control/shift/alt/gui
  Right control/shift/alt/gui

Mac's Command key??? Is Option = Alt? Is Command = GUI?
*/


/*
Keycodes / Scan Codes to support (from https://usb.org/sites/default/files/hut1_21.pdf Chapter 10 / Page 92)


*/


#ifdef HID_TESTING
const uint16_t HIDService::serviceUUID = 0x8812;   // 0x1812 = HID 
#else
const uint16_t HIDService::serviceUUID = 0x1812;   // 0x1812 = HID 
#endif

const uint16_t HIDService::charUUID[ mbbs_cIdxCOUNT ] = { 
#ifdef HID_TESTING
  0x8A4E,  // ProtocolMode
  0x8A4A,  // HIDInfo    
  0x8A4B,  // Keyboard Report Map 
  0x8A4D,  // Keyboard Report
#else
  0x2A4E,  //  ProtocolMode
  0x2A4A,  //  HIDInfo (Confirm Value without BLUETOOTH_PRIVLEDGED exception)   0x2A4A
  0x2A4B,  // Keyboard Report Map
  0x2A4D,  // Keyboard Report 
#endif
};

uint16_t HIDService::HIDInfo[] = { 
  0x0111,
  0x0002
};

// Copied from https://docs.silabs.com/bluetooth/2.13/code-examples/applications/ble-hid-keyboard
// Actually: https://docs.silabs.com/resources/bluetooth/code-examples/applications/ble-hid-keyboard/source/gatt.xml
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
0x95, 0x08, //	Report Count (8) = Above codes are bit mapped to the first byte
0x81, 0x02, //	Input (Data, Variable, Absolute) Modifier byte

0x95, 0x01, //	Report Count (1)
0x75, 0x08, //	Report Size (8)
0x81, 0x01, //	Input (Constant) Reserved byte

0x95, 0x06, //	Report Count (6)
0x75, 0x08, //	Report Size (8)
0x15, 0x00, //	Logical Minimum (0)
0x25, 0x65, //	Logical Maximum (101)
0x05, 0x07, //	Usage Page (Key Codes)
0x19, 0x00, //	Usage Minimum (Reserved (no event indicated))
0x29, 0x65, //	Usage Maximum (Keyboard Application)
0x81, 0x00, //	Input (Data,Array) Key arrays (6 bytes)
0xc0,       //	End Collection
};



/**
 * 
 * 
*/
void HIDService::addReportDescriptor(uint16_t value_handle, uint8_t reportID, uint8_t reportType) {
    ble_gatts_attr_md_t attr_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_srv_report_ref_t rep_ref;

    memset((uint8_t *)&rep_ref, 0, sizeof(rep_ref));
    rep_ref.report_id = reportID;
    rep_ref.report_type = reportType; // Input report

    // Referenced from https://github.com/xueliu/nRF52/blob/master/nRF52_SDK_0.9.1_3639cc9/components/ble/ble_services/ble_hids/ble_hids.c
    uint8_t             encoded_rep_ref[BLE_SRV_ENCODED_REPORT_REF_LEN];
    memset(&attr_md, 0, sizeof(attr_md));
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&attr_md.read_perm); //rep_ref_attr_md.read_perm;
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&attr_md.write_perm); //rep_ref_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_REPORT_REF_DESCR);
    attr_char_value.p_uuid    = &ble_uuid; 
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = ble_srv_report_ref_encode(encoded_rep_ref, &rep_ref); 

    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = attr_char_value.init_len;
    attr_char_value.p_value   = encoded_rep_ref;
    uint16_t ref_handle;// Returned, but discarded
    sd_ble_gatts_descriptor_add(value_handle, 
                                  &attr_char_value,
                                  &ref_handle); 
}
/**
 * Constructor.
 * Create a representation of the Bluetooth SIG Battery Service
 * @param _ble The instance of a BLE device that we're running on.
 */
HIDService::HIDService( BLEDevice &_ble) 
    : protocolMode(0x01) // 0x01 = Report Protocol
{
    DEBUG("HID Serv starting\n");

    // Register the base UUID and create the service.
    bs_uuid_type = BLE_UUID_TYPE_BLE;  // Set the UUID type to 0x01, which should be Bluetooth SIG ID
    CreateService( serviceUUID);
    
    // Create the data structures that represent each of our characteristics in Soft Device.
    CreateCharacteristic( mbbs_cIdxProtocolMode, charUUID[ mbbs_cIdxProtocolMode ],
                        (uint8_t *)&protocolMode,
                        sizeof(protocolMode), sizeof(protocolMode),
                        microbit_propREAD | microbit_propWRITE_WITHOUT ); 

    CreateCharacteristic( mbbs_cIdxHIDInfo, charUUID[ mbbs_cIdxHIDInfo ],
                        (uint8_t *)HIDInfo,
                        sizeof(HIDInfo), sizeof(HIDInfo),
                        microbit_propREAD );
 
    CreateCharacteristic( mbbs_cIdxReportMap, charUUID[ mbbs_cIdxReportMap ],
                        (uint8_t *)reportMap,
                        sizeof(reportMap), sizeof(reportMap),
                        microbit_propREAD  | microbit_propREADAUTH);

    memset(report, 0, sizeof(report));
    CreateCharacteristic( mbbs_cIdxReport, charUUID[ mbbs_cIdxReport ],
                        (uint8_t *)report,
                        sizeof(report), sizeof(report),
                        microbit_propREAD  | microbit_propNOTIFY | microbit_propREADAUTH);

   addReportDescriptor(charHandles( mbbs_cIdxReport)->value, 0, 1 /* Input report */);


  // NEED TO ADD A DESCRIPTOR!


    // memset(bootReport, 0, sizeof(bootReport));
    // CreateCharacteristic( mbbs_cIdxBootKbdInp, charUUID[ mbbs_cIdxBootKbdInp ],
    //                     (uint8_t *)bootReport,
    //                     sizeof(bootReport), sizeof(bootReport),
    //                     microbit_propREAD  | microbit_propNOTIFY | microbit_propREADAUTH);

    // memset(kbtOut, 0, sizeof(kbtOut));
    // CreateCharacteristic( mbbs_cIdxBootKbdOut, charUUID[ mbbs_cIdxBootKbdOut ],
    //                     (uint8_t *)kbtOut,
    //                     sizeof(kbtOut), sizeof(kbtOut),
    //                     microbit_propREAD  | microbit_propWRITE | microbit_propWRITE_WITHOUT);

}


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


#ifdef DEBUG_ENABLED
void HIDService::debugAttribute(int handle) {
      microbit_charattr_t type;
      int index = charHandleToIdx(handle, &type);

      const char *typeName;
      switch(type) {
        case microbit_charattrVALUE:
          typeName = "Value";
          break;
        case microbit_charattrDESC:
          typeName = "Desc";
          break;
        case microbit_charattrCCCD:
          typeName = "CCCD";
          break;
        case microbit_charattrSCCD:
          typeName = "SCCD";
          break;
        default:
          typeName = "UNKNOWN";
      }
      if(index<0 || index>3) index = 4;
      char const *charNames[] = {"Mode", "Info", "Map", "Report", "Invalid"};
      DEBUG("     %s %s\n", charNames[index], typeName);
}
#endif


void HIDService::onDataRead( microbit_onDataRead_t *params) {
      DEBUG("HID. Serv onDataRead\n");
      debugAttribute(params->handle);
}



/**
  * Callback. Invoked when any of our attributes are written via BLE.
  */
void HIDService::onDataWritten( const microbit_ble_evt_write_t *params)
{
    DEBUG("HID. Serv onDataWritten\n");
    debugAttribute(params->handle);
    if(params->handle == valueHandle(mbbs_cIdxProtocolMode)) {
      DEBUG("HID: Data to Protocol");
      protocolMode = params->data[0];
      // 0=>Boot Protocol; 1->Enumeration; ...2.255 ???

      // params->data and params->len
      setChrValue( mbbs_cIdxProtocolMode, (const uint8_t *)&protocolMode, sizeof(protocolMode));
    }
}

void HIDService::sendScanCode(uint8_t c, uint8_t modifiers) {
  memset(report, 0, sizeof(report));
 // memset(bootReport, 0, sizeof(bootReport));

  if(c) {
    report[0] = modifiers;
    report[2] = c;  //b
  }
  notifyChrValue( mbbs_cIdxReport, (uint8_t *)report, sizeof(report)); 
}

void HIDService::sendString(char *str, int len) {
        uint8_t lastCode = 0;
        // Iterate over keys and send them
        DEBUG("Keys: ");
        uint8_t shift = 0;
        uint8_t code = 0;
        for(int i=0; i<len; i++) {
            char c = str[i];
            if(c >= ' ') {  // ASCII character: Get scancode details
                uint16_t full = ascii2scan(c);
                shift = (full>>8) ? HIDService::leftShiftMask : 0;
                code = full & 0xFF;
                // Send blank when repeated keys or just a change in modifier
                if(code == lastCode) {
                    sendScanCode(0, 0);
                    uBit.sleep(betweenKeyDelay);
                }
                sendScanCode(code, shift);

            } else {
                // Special codes
            }
            uBit.sleep(betweenKeyDelay);
            lastCode = code;
            DEBUG("%c (%d%d)",str[i], shift, code);
        }
        // Send final release
        sendScanCode(0, 0);
        DEBUG("\n");
}




#endif