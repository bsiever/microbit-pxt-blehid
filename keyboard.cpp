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

#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "ble_dis.h"

#include "KeyboardReporter.h"
#include "debug.h"

static KeyboardReporter *reporter = NULL;

using namespace pxt;

namespace keyboard { 

    //%
    void startKeyboardService() {
        if(reporter == NULL) {
            reporter = KeyboardReporter::getInstance();
       } 
    }

    //% 
    void sendString(String keys) {
        if(!reporter) return;
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
        if(!reporter) return;

        reporter->sendSimultaneousKeys(keys->ascii.data, keys->ascii.length);
        if(!hold) {
            reporter->sendScanCode(0,0);
        }
    }

    //% 
    void releaseKeys() {
        if(!reporter) return;
        reporter->sendScanCode(0,0);
    }
  }