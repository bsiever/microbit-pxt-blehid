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
// blekeyboard.startKeyboardService()
// serial.writeLine("Done...")

// input.onButtonPressed(Button.A, function () {
//     serial.writeLine("Button A\n")
//     // All printable ASCII characters...
//     blekeyboard.sendString(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
// })

// blekeyboard.setStatusChangeHandler(function () {
//     serial.writeLine("---Status Change---")
//     if (blekeyboard.isEnabled()) {
//         led.plot(0, 0)
//     } else {
//         led.unplot(0, 0)
//     }
// })

// input.onButtonPressed(Button.B, function () {
//     serial.writeLine("Button B\n")
//     for(let i = blekeyboard._Key.enter; i<=blekeyboard._Key.vol_down; i++) {
//         blekeyboard.sendString(blekeyboard.keys(i))
//     }
    
//     for(let i = blekeyboard._Modifier.control; i<=blekeyboard._Modifier.rightWindows; i++) {
//         blekeyboard.sendString(blekeyboard.modifiers(i)+"a")
//     }
// })

// input.onButtonPressed(Button.AB, function () {
//     serial.writeLine("Button AB\n")
//     // // Print an "x" = 0x1b
//     blekeyboard.sendString(blekeyboard.rawScancode(0x1b))

//     blekeyboard.sendSimultaneousKeys(
//                 // blehid.modifiers(Modifier.control)+
//                 // blehid.modifiers(Modifier.alt)+
//                 Modifier.control+Modifier.alt+
//                 "ac"+
//                 Key.enter,     
//             false)

// })




////////////////// Mouse

serial.writeLine("starting...")

bluetooth.onBluetoothConnected(function () {
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
bluetooth.onUartDataReceived(serial.delimiters(Delimiters.NewLine), function () {
    serial.writeLine(bluetooth.uartReadUntil(serial.delimiters(Delimiters.NewLine)))
})
basic.showIcon(IconNames.Yes)
bluetooth.startUartService()
bluetooth.startLEDService()

serial.writeLine("Calling Adv...")
blemouse.startMouseService()
serial.writeLine("Done...")

input.onButtonPressed(Button.A, function () {
    serial.writeLine("Button A\n")
    // All printable ASCII characters...
    blemouse.send();
})

blemouse.setStatusChangeHandler(function () {
    serial.writeLine("---Status Change---")
    if (blemouse.isEnabled()) {
        led.plot(1, 0)
    } else {
        led.unplot(1, 0)
    }
})

