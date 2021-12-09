
//% color=#0000FF 
//% icon="\uf074"
//% block="advertise"
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
