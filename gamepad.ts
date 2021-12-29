
//% color=#0000FF 
//% icon="\uf11b"
//% block="Gamepad"
namespace gamepad {

    //% blockId="gamepad service" block="bluetooth gamepad service"
    //% shim=gamepad::startGamepadService
    //% weight=50
    export function startGamepadService() : void {
    }

    //% shim=gamepad::_send
    function _send(buttons: number, xyrxry: number, dpad: number) : void { 
    }

    // //% blockId="move gamepad xy" block="move gamepad | x by $x| and y by $y"
    // //% x.min=-127 x.max=127 y.min=-127 y.max=127 scroll.min=-127 scroll.max=127
    // //% weight=40
    // export function movexy(x: number, y: number) : void { 
    //     _send(x, y, 0, 0);  
    // }

    // //% blockId="gamepad click" block="click gamepad"
    // //% weight=30
    // export function click() : void { 
    //     _send(0, 0, 0, 0x1);  
    // }

    // //% blockId="gamepad middle click" block="middle click gamepad"
    // //% weight=20
    // export function middleClick() : void { 
    //     _send(0, 0, 0, 0x2);  
    // }
    
    // //% blockId="gamepad right click" block="right click gamepad"
    // //% weight=10
    // export function rightClick() : void { 
    //     _send(0, 0, 0, 0x4);  
    // }

    // //% blockId="scroll gamepad" block="scroll up |by $scroll"
    // //% scroll.min=-127 scroll.max=127
    // //% weight=5
    // export function scroll(scroll: number) : void { 
    //     _send(0, 0, scroll, 0);  
    // }


    function constrain(val: number, min: number, max: number) {
        return (val<min) ? min : (val>max ? max : val);
    }
    //% blockId="send gamepad" block="send gamepad motion|set x to $x|set y to $y| set rx to $rx| set ry to $ry| set buttons to $buttons | set dpad to $dpad" advanced=true
    //% x.min=-127 x.max=127 y.min=-127 y.max=127 rx.min=-127 rx.max=127 ry.min=-127 ry.max=127, dpad.min=0, dpad.max=15
    //% buttons.default=0
    //% blockExternalInputs=true
    //% expandableArgumentMode="toggle"
    //% weight=10
    export function send(buttons: number, x: number, y: number, rx: number, ry: number, dpad: number) : void { 
        x = (constrain(x, -127, 127) & 0xff)
        y = (constrain(y, -127, 127) & 0xff)
        rx = (constrain(rx, -127, 127) & 0xff)
        ry = (constrain(ry, -127, 127) & 0xff)
        let xyrxry = x<<24 | y<<16 | rx<<8 | ry<<0
        _send(buttons, xyrxry, dpad)
    }

    //% blockID="gamepad on status change" block="on gamepad status change" advanced=true
    //% shim=gamepad::setStatusChangeHandler 
    //% weight=20
    export function setStatusChangeHandler(a: Action) {
    }

    //% blockId="gamepad enabled" block="gamepad enabled" advanced=true
    //% shim=gamepad::isEnabled
    //% weight=30
     export function isEnabled() : boolean {
        return false;
    }

}
