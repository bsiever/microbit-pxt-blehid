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

    //% blockId="send string" block="send keys | $keys" 
    //% shim=blemouse::send
    //% weight=40
    export function send() : void {
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
