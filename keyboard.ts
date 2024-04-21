// Key Modifiers
class Modifier {
    static readonly control = "\x01"
    static readonly shift =  "\x02"
    static readonly alt = "\x03"
    static readonly option = "\x03"
    static readonly apple = "\x04"
    static readonly windows = "\x04"
    static readonly rightControl = "\x05"
    static readonly rightShift = "\x06"
    static readonly rightAlt = "\x07"
    static readonly rightOption = "\x07"
    static readonly rightApple = "\x08"
    static readonly rightWindows = "\x08"
}
// Special Keys
class Key {
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

//% color=#0000FF 
//% icon="\uf11c"
//% block="Keyboard"
namespace keyboard {

    //% blockId="keyboard service" block="bluetooth keyboard service"
    //% shim=keyboard::startKeyboardService
    //% weight=50
    export function startKeyboardService() : void {
        return
    }

    //% blockId="send string" block="send keys | $keys" 
    //% shim=keyboard::sendString
    //% weight=40
    export function sendString(keys: string) : void {
        return
    }

    //% blockID="keyboard on status change" block="on keyboard status change" advanced=true
    //% shim=keyboard::setStatusChangeHandler 
    //% weight=20
    export function setStatusChangeHandler(a: Action) {
        return
    }

    //% blockId="keyboard enabled" block="keyboard enabled" advanced=true
    //% shim=keyboard::isEnabled
    //% weight=10
     export function isEnabled() : boolean {
        return false;
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
        //% block="command+"
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
            Modifier.shift,
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
    //% shim=keyboard::sendSimultaneousKeys
    //% weight=50
    export function sendSimultaneousKeys(keys: string, hold: boolean) : void {
        return
    }

    //% blockId="release keys" block="release keys" advanced=true
    //% shim=keyboard::releaseKeys
    //% weight=40
    export function releaseKeys() : void {
        return
    }

    //% block="set events per second | %rate keys/s" advanced=true
    //% rate.min=5 rate.max=30
    //% shim=HIDService::updateEventsPerSecond
    //% weight=50
    export function setEventsPerSecond(rate: number) : void {
        return 
    }
    
}
