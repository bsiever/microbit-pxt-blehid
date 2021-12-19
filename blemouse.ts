// Buttons Modifiers
class MouseButton {
    static readonly left = "\x01"
    static readonly right =  "\x02"
    static readonly middle =  "\x02"
}

//% color=#0000FF 
//% icon="\uf245"
//% block="Mouse"
namespace blemouse {

    //% blockId="mouse service" block="bluetooth mouse service"
    //% shim=blemouse::startMouseService
    //% weight=50
    export function startMouseService() : void {
    }

    //% shim=blemouse::_send
    function _send(x: number, y: number, scroll: number, buttons: number) : void { 
    }

    //% blockId="send mouse" block="send mouse motion|change x by $x|change y by $y|left pressed $left|middle pressed $middle|right pressed $right|change scroll by $scroll|hold buttons $hold" 
    //% x.min=-127 x.max=127 y.min=-127 y.max=127 scroll.min=-127 scroll.max=127
    //% hold.default=false left.default=false middle.default=false right.default=false
    //% blockExternalInputs=true
    //% expandableArgumentMode="toggle"
    //% weight=40
    export function send(x: number, y: number, left: boolean, middle: boolean, right: boolean, scroll: number, hold: boolean) : void { 
        _send(x,y,scroll, (left?0x1:0)|(middle?0x2:0)|(right?0x4:0)|(hold?0x8:0)  )
    }

    //% blockID="mouse on status change" block="on mouse status change" advanced=true
    //% shim=blemouse::setStatusChangeHandler 
    //% weight=20
    export function setStatusChangeHandler(a: Action) {
    }

    //% blockId="mouse enabled" block="mouse enabled" advanced=true
    //% shim=blemouse::isEnabled
    //% weight=10
     export function isEnabled() : boolean {
        return false;
    }

}
