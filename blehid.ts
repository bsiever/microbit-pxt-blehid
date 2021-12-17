
//% color=#0000FF 
//% icon="\uf007"
//% block="HID"
namespace blehid {

    //% blockId="advertise" block="bluetooth HID service"
    //% shim=blehid::startHIDService
    //% weight=50
    export function startHIDService() : void {
    }

    //% blockId="send string" block="send keys | $keys" 
    //% shim=blehid::sendString
    //% weight=40
    export function sendString(keys: string) : void {
    }

    //% blockID="on status change" block="on HID status change" advanced=true
    //% shim=blehid::setStatusChangeHandler 
    //% weight=20
    export function setStatusChangeHandler(a: Action) {
    }

    //% blockId="keyboard enabled" block="keyboard enabled" advanced=true
    //% shim=blehid::keyboardIsEnabled
    //% weight=10
     export function keyboardIsEnabled() : boolean {
        return false;
    }

    export class Modifier {
        static readonly control = "\x10\x01"
        static readonly shift =  "\x10\x02"
        static readonly alt = "\x10\x03"
        static readonly option = "\x10\x03"
        static readonly apple = "\x10\x04"
        static readonly windows = "\x10\x04"
        static readonly rightControl = "\x10\x05"
        static readonly rightShift = "\x10\x06"
        static readonly rightAlt = "\x10\x07"
        static readonly rightOption = "\x10\x07"
        static readonly rightApple = "\x10\x08"
        static readonly rightWindows = "\x10\x08"
    }

    export enum _Modifier {
        //% block="control+"
        control, 
        //% block="shift+"
        shift, 
        //% block="alt+"
        alt, 
        //% block="option+"
        option,
        //% block="control+"
        apple, 
        //% block="windows+"
        windows, 
        //% block="right control+"
        rightControl, 
        //% block="right shift+"
        rightShift, 
        //% block="right alt+"
        rightAlt, 
        //% block="right option+"
        rightOption, 
        //% block="right apple+"
        rightApple, 
        //% block="right windows+"
        rightWindows,
    }

    //% blockId="modifiers" block="%key"
    //% weight=30
    export function modifiers(key : _Modifier) : string {
        let mods = [
            Modifier.control,
            Modifier.alt,
            Modifier.option,
            Modifier.apple,
            Modifier.windows,
            Modifier.rightControl,
            Modifier.rightShift,
            Modifier.rightAlt,
            Modifier.rightOption,
            Modifier.rightApple,
            Modifier.rightWindows]
        if(key>=_Modifier.control && key<=_Modifier.rightWindows)
            return mods[key];

        return ""
    }

    export class Key {
        static readonly enter = "\x10\x28"
        static readonly escape = "\x10\x29"
        static readonly delete = "\x10\x2A"
        static readonly tab = "\x10\x2B"
        static readonly up = "\x10\x52"
        static readonly down = "\x10\x51"
        static readonly left = "\x10\x50"
        static readonly right = "\x10\x4f"
        static readonly vol_up = "\x10\x80"
        static readonly vol_down = "\x10\x81"
    }

    export enum _Key {
        enter,
        escape,
        delete,
        tab,
        up, 
        down,
        left,
        right,
        //% block="volume up"
        vol_up,
        //% block="volume down"
        vol_down,
    }


    //% blockId="key_conv" block="%key"
    //% weight=20
    export function keys(key : _Key) : string {
        let keys = [
            Key.enter,
            Key.escape,
            Key.delete,
            Key.tab,
            Key.up,
            Key.down,
            Key.left,
            Key.right,
            Key.vol_up,
            Key.vol_down            
        ]
        if(key>=_Key.enter && key<=_Key.vol_down)
            return keys[key];
        return "";
    }

    //% block="raw scancode | %code" advanced=true
    //% code.min=0 code.max=255
    //% weight=30
    export function rawScancode(code: number) {
        return "\x10"+String.fromCharCode(code)
    }

    //% blockId="send simultaneous keys" block="send simultaneous keys $keys || hold keys $hold" advanced=true
    //% shim=blehid::sendSimultaneousKeys
    //% weight=50
    export function sendSimultaneousKeys(keys: string, hold: boolean) : void {
    }

    //% blockId="release keys" block="release keys" advanced=true
    //% shim=blehid::releaseKeys
    //% weight=40
    export function releaseKeys() : void {
    }

}


