
// General connection and start-up oriented indications

serial.writeLine("starting...")
bluetooth.onBluetoothConnected(function () {
    serial.writeLine("connected")

    basic.showLeds(`
        . . . . .
        . . . . .
        . . # . #
        . . # # #
        . . . # .
        `)
})
bluetooth.onBluetoothDisconnected(function () {
    basic.showIcon(IconNames.No)
})


// //////////////////////////////// Gamepad /////////////////////////
gamepad.startGamepadService()
serial.writeLine("Gamepad service started...")

// // Infinite loop / prevents all other tests:  
let dpadCmd: number[][] = [[8, 1, 2], [7, 0, 3], [6, 5, 4]]
let buttons = 0
let ud = 0
let y = 0
let x = 0
let lr = 0
let buttonShift = 0
basic.forever(function () {
    lr = 1
    x = input.acceleration(Dimension.X)
    if (x < -300) {
        lr = 0. // Left
    } else if (x > 300) {
        lr = 2. // Right
    }
    y = input.acceleration(Dimension.Y)
    ud = 1
    if (y < -300) {
        ud = 0. // Up
    } else if (y > 300) {
        ud = 2. // Down
    }
    buttons = 0
    if (input.buttonIsPressed(Button.A)) {
        buttons = 1<<buttonShift
        serial.writeLine("Button shift = " + buttonShift)
        buttonShift = (buttonShift + 1) % 15
        // Wait for release / debounce
        while(input.buttonIsPressed(Button.A)) {
            basic.pause(5)
        }
    }
    gamepad.send(
    buttons,
    0,
    0,
    dpadCmd[ud][lr],
    0,
    0
    )
})

// // Test Buttons (via Button A)
// let buttonMask = 1
// input.onButtonPressed(Button.A, function () {
//     serial.writeLine("Button Mask "+buttonMask)
//     gamepad.send(buttonMask, 0, 0, 0, 0, 0);
//     buttonMask = buttonMask*2;
//     if(buttonMask>2**15) {
//         buttonMask = 1;
//     }
// })

// // Test sticks and Hats (D-pads)
// let index = 1
// input.onButtonPressed(Button.B, function () {
//     let vals = [[0,0,0,0,0], [100,0,0,0,0], [0,100,0,0, 0], [0,0,100,0, 0], [0,0,0,100,0],
//      [0,0,0,0,1], [0,0,0,0,2],[0,0,0,0,3],[0,0,0,0,4],[0,0,0,0,5],[0,0,0,0,6],[0,0,0,0,7],[0,0,0,0,8],[0,0,0,0,16],[0,0,0,0,48],[0,0,0,0,32] ]
//     let names = ["-", "x", "y", "rx", "ry", "N1", "NE1", "E2", "SE1", "S1", "SW1", "W1", "NW1", "N2", "NE2", "E2"]
//     gamepad.send(0, vals[index][0], vals[index][1], vals[index][2], vals[index][3], vals[index][4])
//     serial.writeLine(names[index] + " = " + vals[index])
//     index = (index+1) % vals.length
//     // let vals = [10,20,30,40,50,60,70,80,90,100,110,120,-120,-110,-100,-90,-80,-70]
//     // gamepad.send(0, vals[index],0,0,0)
//     // serial.writeLine("x = " + vals[index])
//     // index = (index+1) % vals.length

// })

// Show connection state
gamepad.setStatusChangeHandler(function () {
    serial.writeLine("---Gamepad Status Change---")
    if (gamepad.isEnabled()) {
        serial.writeLine("Enabled")
        led.plot(1, 0)
    } else {
        led.unplot(0, 0)
    }
})


////////////////////////////// Abs Mouse /////////////////////////
// absmouse.startAbsoluteMouseService()
// serial.writeLine("AbsMouse service started...")
//// Button A: Move the mouse top-to-bottom, left-to-right
// input.onButtonPressed(Button.A, function () {
//     for(let x=-32767; x<32767;x+=5000) {
//         for(let y=-32767; y<32767;y+=5000) {
//             serial.writeLine("x " + x + " y " + y)
//             absmouse.movexy(x, y)
//             basic.pause(100)
//         }
//     }
// })
//// Button B: Place mouse a little above/right of center of screen
// input.onButtonPressed(Button.B, function () {
//     absmouse.movexy(-126, -126)
// })
// absmouse.setStatusChangeHandler(function () {
//     serial.writeLine("---Abs Mouse Status Change---")
//     if (absmouse.isEnabled()) {
//         serial.writeLine("Enabled")
//         led.plot(0, 0)
//     } else {
//         led.unplot(0, 0)
//     }
// })



//////////////////////////// Keyboard /////////////////////////
// keyboard.startKeyboardService()
// serial.writeLine("Keyboard service started...")
// // Button AB:  Print "Test"
// input.onButtonPressed(Button.AB, function () {
//     keyboard.sendString("Test")
// })

// // Button A: Print the entire supported ASCII table (and then compare to the string that was sent / is embedded here)
// input.onButtonPressed(Button.A, function () {
//     serial.writeLine("Button A\n")
//     // All printable ASCII characters...
//     keyboard.sendString(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
// })
// // Button B: Iterate through all special keys, then iterate through modifiers+"a"
// input.onButtonPressed(Button.B, function () {
//     serial.writeLine("Button B\n")
//     for(let i = keyboard._Key.enter; i<=keyboard._Key.vol_down; i++) {
//         keyboard.sendString(keyboard.keys(i))
//     }
//     for(let i = keyboard._Modifier.control; i<=keyboard._Modifier.rightWindows; i++) {
//         keyboard.sendString(keyboard.modifiers(i)+"a")
//     }
// })

// keyboard.setStatusChangeHandler(function () {
//     serial.writeLine("---Keyboard Status Change---")
//     if (keyboard.isEnabled()) {
//         serial.writeLine("Enabled")
//         led.plot(0, 0)
//     } else {
//         led.unplot(0, 0)
//     }
// })

// Button A+B: Send a raw scancode and then some simultaneous keys
// input.onButtonPressed(Button.AB, function () {
//     serial.writeLine("Button AB\n")
//     // // Print an "x" = 0x1b
//     keyboard.sendString(keyboard.rawScancode(0x1b))
//     keyboard.sendSimultaneousKeys(
//                 Modifier.control+Modifier.alt+
//                 "ac"+
//                 Key.enter,     
//             false)
// })


////////////////////////////// Media Keys /////////////////////////

// media.startMediaService()
// serial.writeLine("Media service started...")
// // Button A: Hit Play/Pause
// input.onButtonPressed(Button.A, function () {
//     serial.writeLine("Button A\n")
//     media.sendCode(MediaKey.playPause)
// })

// // Iterate through all codes
// input.onButtonPressed(Button.B, function () {
//     serial.writeLine("Button B\n")
//     for(let i = media._MediaKey.next; i<=media._MediaKey.vol_down i++) {
//         media.sendCode(media.keys(i))
//     }
// })

// media.setStatusChangeHandler(function () {
//     serial.writeLine("---Media Status Change---")
//     if (media.isEnabled()) {
//         serial.writeLine("Enabled")
//         led.plot(2, 0)
//     } else {
//         led.unplot(2, 0)
//     }
// })


////////////////////////////// Mouse /////////////////////////
// mouse.startMouseService()
// serial.writeLine("Mouse service started...")
//// Button B: Move mouse 75 units to the right
// input.onButtonPressed(Button.B, function () {
//     serial.writeLine("Button B\n")
//     mouse.send(75, 0, false, false, false, 0, false);
// })
// mouse.setStatusChangeHandler(function () {
//     serial.writeLine("---Mouse Status Change---")
//     if (mouse.isEnabled()) {
//         serial.writeLine("Enabled")
//         led.plot(1, 0)
//     } else {
//         led.unplot(1, 0)
//     }
// })

// Infinite loop / prevents all other tests:  
//  Use the accelerometer to control the mouse
// let y = 0
// let my = 0
// let x = 0
// let mx = 0
// basic.forever(function () {
//     mx = 0
//     x = input.acceleration(Dimension.X)
//     if(x<-300) {
//         mx = Math.map(x, -1023, -400, -127, 0)
//     } else if(x>300) {
//         mx = Math.map(x, 400, 1023, 0, 127)
//     }
//     my = 0
//     y = input.acceleration(Dimension.Y)
//     if(y<-300) {
//         my = Math.map(y, -1023, -400, -127, 0)
//     } else if(y>300) {
//         my = Math.map(y, 400, 1023, 0, 127)
//     }
//     serial.writeValue("mx", mx)
//     serial.writeValue("my", my)
//     blemouse.send(
//         mx,
//         my,
//         input.buttonIsPressed(Button.A),
//         input.buttonIsPressed(Button.B),
//         false,
//         0, 
//         true
//         )
// })


//////// DEBRIS

// bluetooth.onUartDataReceived(serial.delimiters(Delimiters.NewLine), function () {
//     serial.writeLine(bluetooth.uartReadUntil(serial.delimiters(Delimiters.NewLine)))
// })
// bluetooth.startUartService()
// bluetooth.startLEDService()

// bluetooth.onUartDataReceived(serial.delimiters(Delimiters.NewLine), function () {
//     serial.writeLine(bluetooth.uartReadUntil(serial.delimiters(Delimiters.NewLine)))
// })
// basic.showIcon(IconNames.Yes)
// bluetooth.startUartService()
// bluetooth.startLEDService()

// serial.writeLine("Calling Adv...")
