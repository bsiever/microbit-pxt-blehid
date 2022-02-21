
enum GameButton {
    none = 0,
    A = 1<<0,
    B = 1<<1,
    X = 1<<3,
    Y = 1<<4,
    //% block="left shoulder"
    leftShoulder = 1<<6, 
    //% block="right shoulder"
    rightShoulder = 1<<7,
    back = 1<<10,
    start = 1<<11,
    guide = 1<<12,
    //% block="left stick"
    leftStick = 1<<13,
    //% block="right stick"
    rightStick = 1<<14
}

enum GameDirection {
    //% block="no direction"
    noDirection = 0,
    up = 1,
    //% block="up right"
    upRight = 2,
    right = 3,
    //% block="down right"
    downRight = 4,
    down = 5,
    //% block="down left"
    downLeft = 6,
    left = 7,
    //% block="up left"
    upLeft = 8
}

//% color=#ff0000 
//% icon="\uf11b"
//% block="Gamepad"
namespace gamepad {

    //% blockId="gamepad service" block="bluetooth gamepad service"
    //% shim=gamepad::startGamepadService
    //% weight=50
    export function startGamepadService() : void {
        return
    }

    //% shim=gamepad::_send
    function _send(buttons: number, xyzrx: number, dpad: number) : void { 
        return
    }


    //% blockId="dpad_conv" block="D-Pad $direction"
    //% direction.defl=GameDirection.none
    //% weight=20
    export function _dpad(direction: GameDirection): number {
        if (direction < GameDirection.up || direction > GameDirection.upLeft)
            return 0
        return direction
    }

    //% blockId="button_conv" block="Button $button pressed $active"
    //% active.defl=true
    //% button.defl=GameButton.none
    //% weight=20
    export function _buttons(button: GameButton, active: boolean) : number {
        //let active = true
        if(button<GameButton.A || button>GameButton.rightStick)
            return 0
        return active ? button : 0
    }

    function constrain(val: number, min: number, max: number) {
        return (val<min) ? min : (val>max ? max : val);
    }
    
    //% blockId="send gamepad" block="send gamepad motion|set x to $x|set y to $y| set buttons to $buttons | set dpad to $dpad | set z to $z set rx to $rx| " 
    //% x.min=-127 x.max=127 y.min=-127 y.max=127 z.min=-127 z.max=127 rx.min=-127 rx.max=127 dpad.min=0 dpad.max=15
    //% buttons.shadow="button_conv"
    //% dpad.shadow="dpad_conv"
    //% z.defl=0 rx.defl=1
    //% weight=10
    // TODO: Use expandable block (didn't work initially)
    export function send(buttons: number, x: number, y: number, dpad: number, z: number, rx: number) : void {
        x = (constrain(x, -127, 127) & 0xff)
        y = (constrain(y, -127, 127) & 0xff)
        z = (constrain(z, -127, 127) & 0xff)
        rx = (constrain(rx, -127, 127) & 0xff)
        let xyzrx = x<<24 | y<<16 | z<<8 | rx<<0
        _send(buttons, xyzrx, dpad)
    }

    //% blockID="gamepad on status change" block="on gamepad status change" advanced=true
    //% shim=gamepad::setStatusChangeHandler 
    //% weight=20
    export function setStatusChangeHandler(a: Action) {
        return
    }

    //% blockId="gamepad enabled" block="gamepad enabled" advanced=true
    //% shim=gamepad::isEnabled
    //% weight=30
     export function isEnabled() : boolean {
        return false;
    }
}
