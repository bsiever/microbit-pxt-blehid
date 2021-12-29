#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "MediaReporter.h"
#include "debug.h"


// From:
// https://notes.iopush.net/blog/2016/custom-usb-hid-device-descriptor-media-keyboard/
static const uint8_t mediaReportMap[] =
{
0x05, 0x0C,        // Usage Page (Consumer)
0x09, 0x01,        // Usage (Consumer Control)
0xA1, 0x01,        // Collection (Application)
0x85, 0x00,        //   Report ID Offset 7
0x05, 0x0C,        //   Usage Page (Consumer)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x08,        //   Report Count (7)
0x09, 0xB5,        //   Usage (Scan Next Track)
0x09, 0xB6,        //   Usage (Scan Previous Track)
0x09, 0xB7,        //   Usage (Stop)
0x09, 0xB8,        //   Usage (Eject)
0x09, 0xCD,        //   Usage (Play/Pause)
0x09, 0xE2,        //   Usage (Mute)
0x09, 0xE9,        //   Usage (Volume Increment)
0x09, 0xEA,        //   Usage (Volume Decrement)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0xC0,              // End Collection
};

MediaReporter *MediaReporter::reporter = NULL; // Singleton reference to the service

/**
 */
MediaReporter *MediaReporter::getInstance()
{
    if (reporter == NULL)
    {
        reporter = new MediaReporter();
    }
    return reporter;
}

MediaReporter::MediaReporter() : 
    HIDReporter("Media", 1, mediaReportMap, sizeof(mediaReportMap), 7, 108)  // Name and report size
{
} 

void MediaReporter::sendCode(uint8_t code) {
  memset(report, 0, reportSize);
  report[0] = code; 
  sendReport();
}

#endif 