#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "AbsMouseReporter.h"

// Report Map from Nordic SDK Example (app_usbd_hid_mouse_desc.h SDK 17.1.0)
// Modified a bit
// This is 54 bytes
static const uint8_t mouseReportMap[] =
{
  0x05, 0x01,       /* Usage Page (Generic Desktop),       */     \
    0x09, 0x02,       /* Usage (Mouse),                      */     \
    0xA1, 0x01,       /*  Collection (Application),          */     \
    0x09, 0x01,       /*   Usage (Pointer),                  */     \
    0xA1, 0x00,       /*  Collection (Physical),             */     \
    0x85, 0x00,   // Report ID: Offset 11

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
    0x16, 0x01, 0x80,       /*     Logical Minimum (-32767 ),         */     \
    0x26, 0xff, 0x7F,       /*     Logical Maximum (32767 ),          */     \
    0x75, 0x10,       /*     Report Size (16),                */     \
    0x95, 0x02,       /*     Report Count (2)*/     \
    0x81, 0x02,       /*     Input (Data, Variable, Absolute)*/     \
    0xC0,         /*  End Collection,                        */     \
    0xC0,         /* End Collection      */
  };


AbsoluteMouseReporter *AbsoluteMouseReporter::reporter = NULL; // Singleton reference to the service

/**
 */
AbsoluteMouseReporter *AbsoluteMouseReporter::getInstance()
{
    if (reporter == NULL)
    {
        reporter = new AbsoluteMouseReporter();
    }
    return reporter;
}

AbsoluteMouseReporter::AbsoluteMouseReporter() : 
    HIDReporter("Absolute Mouse", 5, mouseReportMap, sizeof(mouseReportMap), 11, 109) // Name and report size
{
    // Done
    DEBUG("Done w/ AbsMouseReporter\n");
}

void AbsoluteMouseReporter::send(uint16_t x, uint16_t y, bool left, bool middle, bool right) {
  DEBUG("Sending Absolute Mouse Report\n");
  memset(report, 0, reportSize);
  report[0] = (left?0x1:0) | (right?0x2:0) | (middle?0x4:0);
  report[1] = x&0xff;
  report[2] = (x>>8)&0xff;
  report[3] = y&0xff;
  report[4] = (y>>8)&0xff;
  sendReport();
}
#endif 