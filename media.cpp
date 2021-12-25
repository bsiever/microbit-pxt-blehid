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

#include "MediaReporter.h"
#include "debug.h"

static MediaReporter *reporter = NULL;

using namespace pxt;

namespace media { 

    bool isInitialized() {
        if(reporter == NULL) {
            uBit.display.scroll("Media not started");
            return false;
        } else {
            return true;
        }
    }
        //%
    void startMediaService() {
        if(reporter == NULL) {
            reporter = MediaReporter::getInstance();
       } 
    }

    //% 
    void sendCode(uint8_t number) {
        if(!isInitialized()) return;
        reporter->sendCode(number);
        reporter->sendCode(0);
    }

    //%
    bool isEnabled() {
        DEBUG("Media isEnabled\n");
        return reporter ? reporter->isEnabled() : false;
    }

    //% 
    void setStatusChangeHandler(Action action) {
        if(!reporter) return;
        reporter->setStatusChangeHandler(action);
    }
  }