
//% color=#0000FF 
//% icon="\uf245"
//% block="Absolute Mouse"
namespace absmouse {

    //% blockId="absolute mouse service" block="bluetooth absolute mouse service"
    //% shim=absmouse::startAbsoluteMouseService
    //% weight=50
    export function startAbsoluteMouseService() : void {
    }

    //% shim=absmouse::_send
    function _send(x: number, y: number, buttons: number) : void { 
    }

    //% blockId="move absolute mouse xy" block="move absolute mouse | x to $x| and y to $y"
    //% x.min=-127 x.max=127 y.min=-127 y.max=127
    //% weight=40
    export function movexy(x: number, y: number) : void { 
        _send(x, y, 0);  
    }

    //% blockId="absolute mouse click" block="click absolute mouse"
    //% weight=30
    export function click() : void { 
        _send(0, 0, 0x1);  
    }

    //% blockId="absolute mouse middle click" block="middle click absolute mouse"
    //% weight=20
    export function middleClick() : void { 
        _send(0, 0, 0x2);  
    }
    
    //% blockId="absolute mouse right click" block="right click absolute mouse"
    //% weight=10
    export function rightClick() : void { 
        _send(0, 0, 0x4);  
    }

    //% blockId="send absolute mouse" block="send absolute mouse motion|set x to $x| and set y to $y|left pressed $left|middle pressed $middle|right pressed $right|change scroll to $scroll|hold buttons $hold" advanced=true
    //% x.min=-127 x.max=127 y.min=-127 y.max=127 
    //% hold.default=false left.default=false middle.default=false right.default=false
    //% blockExternalInputs=true
    //% expandableArgumentMode="toggle"
    //% weight=10
    export function send(x: number, y: number, left: boolean, middle: boolean, right: boolean, hold: boolean) : void { 
        _send(x, y,  (left?0x1:0)|(middle?0x2:0)|(right?0x4:0)|(hold?0x8:0)  )
    }

    //% blockID="absolute mouse on status change" block="on absolute mouse status change" advanced=true
    //% shim=absmouse::setStatusChangeHandler 
    //% weight=20
    export function setStatusChangeHandler(a: Action) {
    }

    //% blockId="absolute mouse enabled" block="absolute mouse enabled" advanced=true
    //% shim=absmouse::isEnabled
    //% weight=30
     export function isEnabled() : boolean {
        return false;
    }

}
