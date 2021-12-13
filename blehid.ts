
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

    export enum Modifier {
        // block="control+"
        control, 
        // block="shift+"
        shift, 
        // block="alt+"
        alt, 
        // block="option+"
        option,
        // block="control+"
        apple, 
        // block="windows+"
        windows, 

        // block="right control+"
        rightControl, 
        // block="right shift+"
        rightShift, 
        // block="right alt+"
        rightAlt, 
        // block="right option+"
        rightOption, 
        // block="right apple+"
        rightApple, 
        // block="right windows+"
        rightWindows,
        _END_
    }

    export enum Key {
        enter,
        escape,
        delete,
        tab,
        up, 
        down,
        left,
        right,
        vol_up,
        vol_down,
        _END_
    }


    //% blockId="modifiers" block="%key"
    export function modifiers(key : Modifier) : string {
        let code = null
        switch(key) {
            case Modifier.control: 
                return "\x01"; 
            case Modifier.shift: 
                return "\x02"; 
            case Modifier.alt: 
            case Modifier.option: 
                return "\x03"; 
            case Modifier.apple: 
            case Modifier.windows: 
                return "\x04"; 
            case Modifier.rightControl: 
                return "\x05"; 
            case Modifier.rightShift: 
                return "\x06"; 
            case Modifier.rightAlt: 
            case Modifier.rightOption: 
                return "\x07"; 
            case Modifier.rightApple: 
            case Modifier.rightWindows: 
                return "\x08"; 
        }
        return ""
    }



    //% blockId="key_conv" block="%key"
    export function keys(key : Key) : string {
        let code = null
        switch(key) {
            case Key.enter: code="\x28"; break;
            case Key.escape: code="\x29"; break;
            case Key.delete: code="\x2A"; break;
            case Key.tab: code="\x2B"; break;
            case Key.up: code = "\x52"; break;
            case Key.down: code = "\x51"; break;
            case Key.left: code = "\x50"; break;
            case Key.right: code = "\x4f"; break;
            case Key.vol_up: code = "\x80"; break;
            case Key.vol_down: code = "\x81"; break;
        }
        if(code!=null) {
            return "\x10"+code;
        } else {
            return "";
        }
    }

    //% block="raw scancode" 
    //% code.min = 0 code.max=255
    export function rawScancode(code: number) {
        return "\x10"+String.fromCharCode(code)
    }



}


