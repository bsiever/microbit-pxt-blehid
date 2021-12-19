#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "BLEMouseService.h"
#include "ascii2scan.h"

// Report Map from Nordic SDK Example (app_usbd_hid_mouse_desc.h SDK 17.1.0)
static uint8_t mouseReportMap[] =
{
    0x05, 0x01,       /* Usage Page (Generic Desktop),       */     \
    0x09, 0x02,       /* Usage (Mouse),                      */     \
    0xA1, 0x01,       /*  Collection (Application),          */     \
    0x09, 0x01,       /*   Usage (Pointer),                  */     \
    0xA1, 0x00,       /*  Collection (Physical),             */     \
    0x05, 0x09,       /*     Usage Page (Buttons),           */     \
    0x19, 0x01,       /*     Usage Minimum (01),             */     \
    0x29, 0x03,       /*     Usage Maximum (bcnt),           */     \
    0x15, 0x00,       /*     Logical Minimum (0),            */     \
    0x25, 0x01,       /*     Logical Maximum (1),            */     \
    0x75, 0x01,       /*     Report Size (1),                */     \
    0x95, 0x03,       /*     Report Count (bcnt),            */     \
    0x81, 0x02,       /*     Input (Data, Variable, Absolute)*/     \
    0x75, (8-(3)), /*     Report Size (8-(bcnt)),         */     \
    0x95, 0x01,       /*     Report Count (1),               */     \
    0x81, 0x01,       /*     Input (Constant),               */     \
    0x05, 0x01,       /*     Usage Page (Generic Desktop),   */     \
    0x09, 0x30,       /*     Usage (X),                      */     \
    0x09, 0x31,       /*     Usage (Y),                      */     \
    0x09, 0x38,       /*     Usage (Scroll),                 */     \
    0x15, 0x81,       /*     Logical Minimum (-127),         */     \
    0x25, 0x7F,       /*     Logical Maximum (127),          */     \
    0x75, 0x08,       /*     Report Size (8),                */     \
    0x95, 0x03,       /*     Report Count (3),               */     \
    0x81, 0x06,       /*     Input (Data, Variable, Relative)*/     \
    0xC0,         /*  End Collection,                        */     \
    0xC0,         /* End Collection      */
  };

static uint8_t mouseReport[4] = {0};

BLEMouseService::BLEMouseService( BLEDevice &_ble) : 
    HIDService(_ble, 
              mouseReportMap, sizeof(mouseReportMap), 
              mouseReport, sizeof(mouseReport),
              110, // uBit Event ID
              "Mouse"
    ) 
{
    // Done
}

void BLEMouseService::send(uint8_t dx, uint8_t dy, bool left, bool middle, bool right, uint8_t dscroll) {
  DEBUG("Sending Mouse Report\n");
  memset(mouseReport, 0, sizeof(mouseReport));
  mouseReport[0] = (left?0x1:0) | (middle?0x2:0) | (right?0x4:0);
  mouseReport[1] = dx;
  mouseReport[2] = dy; 
  mouseReport[3] = dscroll;
  notifyChrValue( mbbs_cIdxReport, (uint8_t *)mouseReport, sizeof(mouseReport)); 
}

#endif 