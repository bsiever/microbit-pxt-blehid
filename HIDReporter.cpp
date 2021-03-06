#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "HIDReporter.h"
#include "HIDService.h"

HIDReporter::HIDReporter(const char *_name, const int _reportSize, const uint8_t *_reportMap, const int _reportMapSize, int _reportIDOffset, int _eventID) :
    name(_name),  
    enabled(false), 
    reportIndex(-1),
    reportID(-1),
    report(NULL),
    reportSize(_reportSize), 
    reportIDOffset(_reportIDOffset),
    reportMap(_reportMap), 
    reportMapSize(_reportMapSize), 
    eventID(_eventID)
{
    DEBUG("Name %s ReportSize %d\n", name, reportMapSize);
    // Get the instance of the HID service
    HIDService *hidService = HIDService::getInstance();
    // Add this object
    hidService->addReporter(this);
    report = hidService->getReportBuffer(reportIndex);
}
 
void HIDReporter::sendReport() {
    //DEBUG("Send Notify %d (size %d)\n", reportIndex, reportSize);
    // Get the instance of the HID service
    HIDService *hidService = HIDService::getInstance();
    // Notify with new data
    hidService->notifyChrValue(reportIndex, report, reportSize);    
}

void HIDReporter::setStatusChangeHandler(Action action) {
    registerWithDal(eventID, HIDService::EVT_STATUS, action);
}

void HIDReporter::setEnabled(bool status) {
  DEBUG("%s Setting Enabled %d;  id %d\n", name, status, eventID);
  enabled = status;
  MicroBitEvent(eventID, HIDService::EVT_STATUS);
}
#endif