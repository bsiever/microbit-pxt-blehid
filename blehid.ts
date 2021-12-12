
//% color=#0000FF 
//% icon="\uf007"
//% block="HID"
namespace blehid {

    //% blockId="advertise" block="bluetooth HID service"
    //% shim=blehid::startHIDService
    export function startHIDService() : void {
    }

    //% blockId="send string" block="send keys | $keys" 
    //% shim=blehid::sendString
    export function sendString(keys: string) : void {
    }

    //% blockID="on status change" block="on HID status change" advanced=true
    //% shim=blehid::setStatusChangeHandler 
    export function setStatusChangeHandler(a: Action) {
    }

    //% blockId="keyboard enabled" block="keyboard enabled" advanced=true
    //% shim=blehid::keyboardIsEnabled
    export function keyboardIsEnabled() : boolean {
        return false;
    }
}
