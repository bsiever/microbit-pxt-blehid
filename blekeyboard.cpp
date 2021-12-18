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

#include "BLEHIDKeyboard.h"
#include "debug.h"


static BLEHIDKeyboard *hids = NULL;

using namespace pxt;

namespace blekeyboard { 

    //%
    void startKeyboardService() {
        if(hids == NULL) {
            hids = new ::BLEHIDKeyboard(*uBit.ble);
       }
    }

    //% 
    void sendString(String keys) {
        if(!hids) return;
        hids->sendString(keys->ascii.data, keys->ascii.length);
    }

    //%
    bool isEnabled() {
        DEBUG("blekeyboard isEnabled in kbd\n");
        return hids ? hids->isEnabled() : false;
    }

    //% 
    void setStatusChangeHandler(Action action) {
        DEBUG("blekeyboard Setting Status Changed Handler\n");
        if(!hids) return;
        hids->setStatusChangeHandler(action);
    }


    //% 
    void sendSimultaneousKeys(String keys, bool hold) {
        if(!hids) return;

        hids->sendSimultaneousKeys(keys->ascii.data, keys->ascii.length);
        if(!hold) {
            hids->sendScanCode(0,0);
        }
    }

    //% 
    void releaseKeys() {
        if(!hids) return;
        hids->sendScanCode(0,0);
    }

  }