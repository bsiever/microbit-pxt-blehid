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

#include "MouseReporter.h"
#include "debug.h"

static MouseReporter *reporter = NULL;

static int constrain(int in, int min, int max) {
    return (in<min)?min:(in>max?max:in);
}

using namespace pxt; 

namespace mouse { 

    bool isInitialized() {
        if(reporter == NULL) {
            uBit.display.scroll("Mouse not started");
            return false;
        } else {
            return true;
        }
    }

    //%
    void startMouseService() {
        if(reporter == NULL) {
            reporter = MouseReporter::getInstance();
        }
    }

    //% 
    void _send(int dx, int dy, int scroll, int buttons) {
        if(!isInitialized()) return;
        dx = constrain(dx,-127, 127);
        dy = constrain(dy,-127, 127);
        scroll = constrain(scroll,-127, 127);
        
        reporter->send(dx, dy, buttons&0x1, buttons&0x2, buttons&0x4, scroll);
        if(!(buttons&0x8)) 
            reporter->send(0,0,false, false, false, 0);
    }

    //%
    bool isEnabled() {
        return reporter ? reporter->isEnabled() : false;
    }

    //% 
    void setStatusChangeHandler(Action action) {
        if(!reporter) return;
        reporter->setStatusChangeHandler(action);
    }
  }