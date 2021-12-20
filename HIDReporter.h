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

    unsigned reportIndex; // Actual index into characteristics
    unsigned reportID;
    uint8_t *report;
    const int reportSize;
    const int reportIDOffset;

    const uint8_t *reportMap;
    const int reportMapSize;
    const int eventID; 
    void sendReport();
    void setEnabled(bool status);
};


#endif