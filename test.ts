serial.writeLine("starting...")

bluetooth.onBluetoothConnected(function () {
    basic.showIcon(IconNames.Heart)
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
    serial.writeLine("Button 2...\n")
//    blehid.setBatteryLevel(50)
    blehid.sendString("Hello, World!");
})