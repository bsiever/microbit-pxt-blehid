#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "BLEKeyboardService.h"
#include "ascii2scan.h"

const int SHIFT_MASK =  0x02;

 // Copied from https://docs.silabs.com/bluetooth/2.13/code-examples/applications/ble-hid-keyboard
// Actually: https://docs.silabs.com/resources/bluetooth/code-examples/applications/ble-hid-keyboard/source/gatt.xml
static uint8_t keyboardReportMap[] =
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

static uint8_t keyboardReport[8] = {0};

BLEKeyboardService::BLEKeyboardService( BLEDevice &_ble) : 
    HIDService(_ble, 
              keyboardReportMap, sizeof(keyboardReportMap), 
              keyboardReport, sizeof(keyboardReport),
              109, // uBit Event ID
              "Keyboard"
    ) 
{
    // Done
    // May need to add protocol characteristic for report protocol
}

void BLEKeyboardService::sendScanCode(uint8_t c, uint8_t modifiers) {
  memset(keyboardReport, 0, sizeof(keyboardReport));

  if(c) {
    keyboardReport[0] = modifiers;
    keyboardReport[2] = c;  //b
  }
  notifyChrValue( mbbs_cIdxReport, (uint8_t *)keyboardReport, sizeof(keyboardReport)); 
}

void BLEKeyboardService::sendSimultaneousKeys(char *str, int len) {
  uint8_t modifiers = 0;
  memset(keyboardReport, 0, sizeof(keyboardReport));
  int idx = 2;  // Report index
  // Process the string / build the report
  for(int i=0; i<len && idx<sizeof(keyboardReport); i++) {
    char c = str[i];
    // Check for modifiers
    if(c>=1 && c<=8) {
      modifiers |= 1<<(c-1);
      // Check for direct scan code
    } else if(c==0x10) { 
      i++; // Advance to next character if valid
      if(i<len) {
        keyboardReport[idx++] = str[i];
      }
      // Regular ASCII character
    } else if(c>=' ') {
      uint16_t full = ascii2scan(c);
      modifiers |= (full>>8) ? SHIFT_MASK : 0;
      keyboardReport[idx++] = full & 0xFF;
    }
  }
  keyboardReport[0] = modifiers;
  notifyChrValue( mbbs_cIdxReport, (uint8_t *)keyboardReport, sizeof(keyboardReport)); 
}


void BLEKeyboardService::sendString(char *str, int len) {
        uint8_t lastCode = 0;
        // Iterate over keys and send them
        DEBUG("Keys: ");
        uint8_t shift = 0;
        uint8_t code = 0;
        for(int i=0; i<len; i++) {
            char c = str[i];
            if(c >= ' ') {  // ASCII character: Get scancode details
                uint16_t full = ascii2scan(c);
                shift = (full>>8) ? SHIFT_MASK : 0;
                code = full & 0xFF;
                // Send blank when repeated keys or just a change in modifier

                // TODO: Is this needed???
                if(code == lastCode) {
                    sendScanCode(0, 0);
                    uBit.sleep(betweenKeyDelay);
                }
                sendScanCode(code, shift);

            } else {
                // Handle control codes
                uint8_t modifiers = 0;
                while(str[i]>=1 && str[i]<=8 && i<len) {
                  modifiers |= 1<<(str[i]-1);
                  i++;
                }
                if(i<len) {
                  // Check for raw scancode
                  if(str[i]==0x10) {
                    if(i+1<len) {
                      i++;
                      code = str[i]; 
                    } else {
                      code = 0;  // Scancode expected, but not there. Default to nothing.
                    }
                  } else {
                    uint16_t full = ascii2scan(str[i]);
                    modifiers |= (full>>8) ? SHIFT_MASK : 0;
                    code = full & 0xFF;
                  }
                  i++;
                  sendScanCode(code, modifiers);
                }

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