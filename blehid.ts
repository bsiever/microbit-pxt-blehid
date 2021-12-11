
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

}
