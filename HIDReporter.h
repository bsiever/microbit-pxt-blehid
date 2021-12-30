#ifndef HID_REPORTER_H
#define HID_REPORTER_H

#include "pxt.h"
#include "MicroBit.h"


class HIDReporter {

public: 
    bool isEnabled() { return enabled; }
    void setStatusChangeHandler(Action action);
    
    // Each subclass should have a getInstance() to return a singleton

protected:
    HIDReporter(const char* _name, const int _reportSize, 
                const uint8_t *_reportMap, const int _reportMapSize, 
                int _reportIDOffset,
                int _eventID);
    friend class HIDService;


    const char* name;
    bool enabled;

    unsigned reportIndex;      // Actual index into characteristics
    unsigned reportID;         // The report ID that will be used for corresponding reports
    uint8_t *report;           // Buffer to be used for report data
    const int reportSize;      // Size of the reports
    const int reportIDOffset;  // 0-based offset of report ID in report map

    const uint8_t *reportMap;  // The report map (must include a report ID)
    const int reportMapSize;   // Size of report
    const int eventID;         // Event ID used to notify of changes in report CCCD status

    void sendReport();
    void setEnabled(bool status);
};
#endif