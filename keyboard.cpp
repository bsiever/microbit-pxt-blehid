/**
* Bill Siever
* 2021-11-20 Initial Version
*
* Development environment specifics:
* Written in Microsoft PXT
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions 
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.
*/

#include "pxt.h"
#include "MicroBit.h"

#include "KeyboardReporter.h"
#include "HIDService.h"
#include "debug.h"

static KeyboardReporter *reporter = NULL;

using namespace pxt;

namespace keyboard { 

    bool isInitialized() {
        if(reporter == NULL) {
            uBit.display.scroll("Keyboard not started");
            return false;
        } else {
            return true;
        }
    }

    //%
    void startKeyboardService() {
        if(reporter == NULL) {
            reporter = KeyboardReporter::getInstance();
       } 
    }

    //% 
    void sendString(String keys) {
        if(!isInitialized()) return;
        reporter->sendString(keys->ascii.data, keys->ascii.length);
    }

    //%
    bool isEnabled() {
        DEBUG("Keyboard isEnabled\n");
        return reporter ? reporter->isEnabled() : false;
    }

    //% 
    void setStatusChangeHandler(Action action) {
        if(!reporter) return;
        reporter->setStatusChangeHandler(action);
    }

    //% 
    void sendSimultaneousKeys(String keys, bool hold) {
        if(!isInitialized()) return;

        reporter->sendSimultaneousKeys(keys->ascii.data, keys->ascii.length);
        if(!hold) {
            reporter->sendScanCode(0,0);
        }
    }

    //% 
    void releaseKeys() {
        if(!isInitialized()) return;
        reporter->sendScanCode(0,0);
    }

    //% 
    void setEventsPerSecond(uint32_t rate) {
        HIDService::setEventsPerSecond(rate);
    }

  }