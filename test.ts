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
blehid.startHIDService()
serial.writeLine("Done...")

input.onButtonPressed(Button.A, function () {
    serial.writeLine("Button A\n")
    // All printable ASCII characters...
    blehid.sendString(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
})

blehid.setStatusChangeHandler(function () {
    serial.writeLine("Status Change")
    if (blehid.keyboardIsEnabled()) {
        led.plot(0, 0)
    } else {
        led.unplot(0, 0)
    }
})

input.onButtonPressed(Button.B, function () {
    serial.writeLine("Button B\n")
    for(let i = Key.enter; i<Key._END_; i++) {
        blehid.sendString(blehid.keys(i))
    }
})
