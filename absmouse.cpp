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

#include "AbsMouseReporter.h"
#include "debug.h"

static AbsoluteMouseReporter *reporter = NULL;

static int constrain(int in, int min, int max) {
    return (in<min)?min:(in>max?max:in);
}

using namespace pxt; 

namespace absmouse {
    static int lastX = 0;
    static int lastY = 0;

    bool isInitialized() {
        if(reporter == NULL) {
            uBit.display.scroll("Absolute Mouse not started");
            return false;
        } else {
            return true;
        }
    }

    //%
    void startAbsoluteMouseService() {
        if(reporter == NULL) {
            reporter = AbsoluteMouseReporter::getInstance();
        }
    }

    //% 
    void _send(int x, int y, int buttons) {
        if(!isInitialized()) return;

        x = x==0xFFFF ? lastX : x;
        y = y==0xFFFF ? lastY : y;

        x = constrain(x,-32767, 32767);
        y = constrain(y,-32767, 32767);
        
        reporter->send(x, y, buttons&0x1, buttons&0x2, buttons&0x4);

        if(!(buttons&0x8)) 
            reporter->send(x,y,false, false, false);
        lastX = x;
        lastY = y;
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