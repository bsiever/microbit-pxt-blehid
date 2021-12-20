
// Special Keys
class MediaKey {
    static readonly next = 0x01
    static readonly previous = 0x02
    static readonly stop = 0x04
    static readonly eject = 0x08
    static readonly playPause = 0x10
    static readonly mute = 0x20
    static readonly vol_up = 0x40
    static readonly vol_down = 0x80
}

//% color=#0000FF 
//% icon="\uf04b"
//% block="Media"
namespace media {

    //% blockId="media service" block="bluetooth media service"
    //% shim=media::startMediaService
    //% weight=50
    export function startMediaService() : void {
    }

    //% blockId="send code" block="send code | $code" 
    //% shim=media::sendCode
    //% weight=40
    export function sendCode(code: number) : void {
    }

    //% blockID="media on status change" block="on media status change" advanced=true
    //% shim=media::setStatusChangeHandler 
    //% weight=20
    export function setStatusChangeHandler(a: Action) {
    }

    //% blockId="media enabled" block="media enabled" advanced=true
    //% shim=media::isEnabled
    //% weight=10
     export function isEnabled() : boolean {
        return false;
    }

    export enum _MediaKey {
        next, 
        previous, 
        stop, 
        eject, 
        //% block="play/pause"        
        playPause,
        mute,
        //% block="volume up"
        vol_up,
        //% block="volume down"
        vol_down,
    }

    //% blockId="key_conv" block="%key"
    //% weight=20
    export function keys(key : _MediaKey) : number {
        let keys = [
            MediaKey.next, 
            MediaKey.previous, 
            MediaKey.stop, 
            MediaKey.eject, 
            MediaKey.playPause,
            MediaKey.mute,
            MediaKey.vol_up, 
            MediaKey.vol_down  
        ]
        if(key>=_MediaKey.next && key<=_MediaKey.vol_down)
            return keys[key];
        return 0;
    }
}
