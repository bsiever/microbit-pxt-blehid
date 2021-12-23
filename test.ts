serial.writeLine("starting...")


input.onButtonPressed(Button.A, function () {
    absmouse.movexy(126, 126)
})

input.onButtonPressed(Button.B, function () {
    absmouse.movexy(-126, -126)
})

input.onButtonPressed(Button.AB, function () {
    keyboard.sendString("Test")
})
keyboard.startKeyboardService()
absmouse.startAbsoluteMouseService()



absmouse.setStatusChangeHandler(function () {
    serial.writeLine("---Abs Mouse Status Change---")
    if (absmouse.isEnabled()) {
        serial.writeLine("Enabled")
        led.plot(0, 0)
    } else {
        led.unplot(0, 0)
    }
})


// bluetooth.onBluetoothConnected(function () {
//     serial.writeLine("connected")

//     basic.showLeds(`
//         . . . . .
//         . . . . .
//         . . # . #
//         . . # # #
//         . . . # .
//         `)
// })
// bluetooth.onBluetoothDisconnected(function () {
//     basic.showIcon(IconNames.No)
// })

// basic.showIcon(IconNames.Yes)








// bluetooth.onUartDataReceived(serial.delimiters(Delimiters.NewLine), function () {
//     serial.writeLine(bluetooth.uartReadUntil(serial.delimiters(Delimiters.NewLine)))
// })
// bluetooth.startUartService()
// bluetooth.startLEDService()


// media.startMediaService()
// input.onButtonPressed(Button.A, function () {
//     serial.writeLine("Button A\n")
//     media.sendCode(MediaKey.playPause)
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


// serial.writeLine("Calling Adv...")
// keyboard.startKeyboardService()

// serial.writeLine("Done...")
// input.onButtonPressed(Button.A, function () {
//     serial.writeLine("Button A\n")
//     // All printable ASCII characters...
//     keyboard.sendString(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
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

// input.onButtonPressed(Button.B, function () {
//     serial.writeLine("Button B\n")
//     for(let i = keyboard._Key.enter; i<=keyboard._Key.vol_down; i++) {
//         keyboard.sendString(keyboard.keys(i))
//     }
    
//     for(let i = keyboard._Modifier.control; i<=keyboard._Modifier.rightWindows; i++) {
//         keyboard.sendString(keyboard.modifiers(i)+"a")
//     }
// })

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









////////////////// Mouse

// serial.writeLine("starting...")

// bluetooth.onBluetoothConnected(function () {
//     basic.showLeds(`
//         . . . . .
//         . . . . .
//         . . # . #
//         . . # # #
//         . . . # .
//         `)
// })
// bluetooth.onBluetoothDisconnected(function () {
//     basic.showIcon(IconNames.No)
// })
// bluetooth.onUartDataReceived(serial.delimiters(Delimiters.NewLine), function () {
//     serial.writeLine(bluetooth.uartReadUntil(serial.delimiters(Delimiters.NewLine)))
// })
// basic.showIcon(IconNames.Yes)
// bluetooth.startUartService()
// bluetooth.startLEDService()

// serial.writeLine("Calling Adv...")
// mouse.startMouseService()
// serial.writeLine("Done...")

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

// let y = 0
// let my = 0
// let x = 0
// let mx = 0
// basic.showIcon(IconNames.Heart)
// blemouse.startMouseService()
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