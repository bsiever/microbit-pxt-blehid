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

static int constrain(int in, int min, int max) {
    return (in<min)?min:(in>max?max:in);
}

using namespace pxt;

namespace blemouse { 

    //%
    void startMouseService() {
        if(hids == NULL) {
            hids = new ::BLEMouseService(*uBit.ble);
       }
    }

    //% 
    void send(int dx, int dy, int scroll, int buttons) {
        if(!hids) return;
        dx = constrain(dx,-127, 127);
        dy = constrain(dy,-127, 127);
        scroll = constrain(scroll,-127, 127);
        
        hids->send(dx, dy, buttons&0x1, buttons&0x2, buttons&0x4, scroll);
        if(!(buttons&0x8)) 
            hids->send(0,0,false, false, false, 0);
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