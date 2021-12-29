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

#include "GamepadReporter.h"
#include "debug.h"


static GamepadReporter *reporter = NULL;

using namespace pxt; 

namespace gamepad { 

    bool isInitialized() {
        if(reporter == NULL) {
            uBit.display.scroll("Gamepad not started");
            return false;
        } else {
            return true;
        }
    }

    //%
    void startGamepadService() {
        if(reporter == NULL) {
            reporter = GamepadReporter::getInstance();
        }
    }

    //% 
    void _send(uint16_t buttons, uint32_t xyrxry, uint8_t dpad) {
        if(!isInitialized()) return;
        uint8_t x = (xyrxry >> 24)&0xFF;
        uint8_t y = (xyrxry >> 16)&0xFF;
        uint8_t rx = (xyrxry >>  8)&0xFF;
        uint8_t ry = (xyrxry >>  0)&0xFF;

        DEBUG("x %d, y %d rx %d, ry %d, dpad: 0x%02x\n",x,y,rx,ry, dpad);
        reporter->send(buttons, x, y, rx, ry, dpad);
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