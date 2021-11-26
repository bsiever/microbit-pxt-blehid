
//% color=#0000FF 
//% icon="\uf074"
//% block="advertise"
namespace blehid {
    //% blockId="advertise" block="bluetooth HID service"
    //% shim=blehid::startHIDService
    export function startHIDService() : void {
    }

    //% blockId="set battery level" block="set battery level to | $level %"
    //% shim=blehid::setBatteryLevel
    //% level.min=0 level.max=100
    export function setBatteryLevel(level: number) : void {
    }

    //% blockId="send string" block="send keys %" 
    //% shim=blehid::sendString
    export function sendString() : void {
    }

}
