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

#include "BLEMouseService.h"
#include "debug.h"


static BLEMouseService *hids = NULL;

using namespace pxt;

namespace blemouse { 

    //%
    void startMouseService() {
        if(hids == NULL) {
            hids = new ::BLEMouseService(*uBit.ble);
       }
    }

    //% 
    void send() {
        if(!hids) return;
        hids->send();
    }

    //%
    bool isEnabled() {
        DEBUG("blemouse isEnabled\n");
        return hids ? hids->isEnabled() : false;
    }

    //% 
    void setStatusChangeHandler(Action action) {
        DEBUG("blemouse Setting Status Changed Handler\n");
        if(!hids) return;
        hids->setStatusChangeHandler(action);
    }

  }