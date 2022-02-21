
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


// // //////////////////////////////// Gamepad /////////////////////////
// gamepad.startGamepadService()
// serial.writeLine("Gamepad service started...")

// // // Infinite loop / prevents all other tests:  
// let dpadCmd: number[][] = [[GameDirection.upLeft,   GameDirection.up,          GameDirection.upRight], 
//                            [GameDirection.left,     GameDirection.noDirection, GameDirection.right],
//                            [GameDirection.downLeft, GameDirection.down,        GameDirection.downRight]]
// let buttons = 0
// let ud = 0
// let y = 0
// let x = 0
// let lr = 0
// let buttonShift = 0
// basic.forever(function () {
//     lr = 1
//     x = input.acceleration(Dimension.X)
//     if (x < -300) {
//         lr = 0. // Left
//     } else if (x > 300) {
//         lr = 2. // Right
//     }
//     y = input.acceleration(Dimension.Y)
//     ud = 1
//     if (y < -300) {
//         ud = 0. // Up
//     } else if (y > 300) {
//         ud = 2. // Down
//     }
//     buttons = 0
//     // if (input.buttonIsPressed(Button.A)) {
//     //     buttons = 1<<buttonShift
//     //     serial.writeLine("Button shift = " + buttonShift)
//     //     buttonShift = (buttonShift + 1) % 15
//     //     // Wait for release / debounce
//     //     while(input.buttonIsPressed(Button.A)) {
//     //         basic.pause(5)
//     //     }
//     // }    buttons = 0

//     // First two buttons only. 
//     buttons = (input.buttonIsPressed(Button.A) ? 1 : 0) | 
//               (input.buttonIsPressed(Button.B) ? 2 : 0) 
//     // D-Pad Control (binary)
//     // gamepad.send(
//     //     buttons,
//     //     0,
//     //     0,
//     //     dpadCmd[ud][lr],
//     //     0,
//     //     0
//     //     )
//     // x/y Control (analog)
//     gamepad.send(
//         buttons,
//         Math.map(x, -1023, 1023, -126, 126),
//         Math.map(y, -1023, 1023, -126, 126),
//         0,
//         0,
//         0
//         )
// })

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
// gamepad.setStatusChangeHandler(function () {
//     serial.writeLine("---Gamepad Status Change---")
//     if (gamepad.isEnabled()) {
//         serial.writeLine("Enabled")
//         led.plot(1, 0)
//     } else {
//         led.unplot(0, 0)
//     }
// })


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


//  Keyboard extreme

// bluetooth.onBluetoothConnected(function () {
//     basic.showIcon(IconNames.Heart)
// })

// input.onButtonPressed(Button.B, function () {
//     keyboard.sendString("A-B-C  way-in short")
// })
// input.onButtonPressed(Button.A, function () {
//     keyboard.sendString("It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way - in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.  There were a king with a large jaw and a queen with a plain face, on the throne of England; there were a king with a large jaw and a queen with a fair face, on the throne of France. In both countries it was clearer than crystal to the lords of the State preserves of loaves and fishes, that things in general were settled for ever.  It was the year of Our Lord one thousand seven hundred and seventy-five. Spiritual revelations were conceded to England at that favoured period, as at this. Mrs. Southcott had recently attained her five-and-twentieth blessed birthday, of whom a prophetic private in the Life Guards had heralded the sublime appearance by announcing that arrangements were made for the swallowing up of London and Westminster. Even the Cock-lane ghost had been laid only a round dozen of years, after rapping out its messages, as the spirits of this very year last past (supernaturally deficient in originality) rapped out theirs. Mere messages in the earthly order of events had lately come to the English Crown and People, from a congress of British subjects in America: which, strange to relate, have proved more important to the human race than any communications yet received through any of the chickens of the Cock-lane brood.  France, less favoured on the whole as to matters spiritual than her sister of the shield and trident, rolled with exceeding smoothness down hill, making paper money and spending it. Under the guidance of her Christian pastors, she entertained herself, besides, with such humane achievements as sentencing a youth to have his hands cut off, his tongue torn out with pincers, and his body burned alive, because he had not kneeled down in the rain to do honour to a dirty procession of monks which passed within his view, at a distance of some fifty or sixty yards. It is likely enough that, rooted in the woods of France and Norway, there were growing trees, when that sufferer was put to death, already marked by the Woodman, Fate, to come down and be sawn into boards, to make a certain movable framework with a sack and a knife in it, terrible in history. It is likely enough that in the rough outhouses of some tillers of the heavy lands adjacent to Paris, there were sheltered from the weather that very day, rude carts, bespattered with rustic mire, snuffed about by pigs, and roosted in by poultry, which the Farmer, Death, had already set apart to be his tumbrils of the Revolution. But that Woodman and that Farmer, though they work unceasingly, work silently, and no one heard them as they went about with muffled tread: the rather, forasmuch as to entertain any suspicion that they were awake, was to be atheistical and traitorous.  In England, there was scarcely an amount of order and protection to justify much national boasting. Daring burglaries by armed men, and highway robberies, took place in the capital itself every night; families were publicly cautioned not to go out of town without removing their furniture to upholsterers' warehouses for security; the highwayman in the dark was a City tradesman in the light, and, being recognised and challenged by his fellow-tradesman whom he stopped in his character of ''the Captain,'' gallantly shot him through the head and rode away; the mail was waylaid by seven robbers, and the guard shot three dead, and then got shot dead himself by the other four, ''in consequence of the failure of his ammunition:'' after which the mail was robbed in peace; that magnificent potentate, the Lord Mayor of London, was made to stand and deliver on Turnham Green, by one highwayman, who despoiled the illustrious creature in sight of all his retinue; prisoners in London gaols fought battles with their turnkeys, and the majesty of the law fired blunderbusses in among them, loaded with rounds of shot and ball; thieves snipped off diamond crosses from the necks of noble lords at Court drawing-rooms; musketeers went into St. Giles's, to search for contraband goods, and the mob fired on the musketeers, and the musketeers fired on the mob, and nobody thought any of these occurrences much out of the common way. In the midst of them, the hangman, ever busy and ever worse than useless, was in constant requisition; now, stringing up long rows of miscellaneous criminals; now, hanging a housebreaker on Saturday who had been taken on Tuesday; now, burning people in the hand at Newgate by the dozen, and now burning pamphlets at the door of Westminster Hall; to-day, taking the life of an atrocious murderer, and to-morrow of a wretched pilferer who had robbed a farmer's boy of sixpence.  All these things, and a thousand like them, came to pass in and close upon the dear old year one thousand seven hundred and seventy-five. Environed by them, while the Woodman and the Farmer worked unheeded, those two of the large jaws, and those other two of the plain and the fair faces, trod with stir enough, and carried their divine rights with a high hand. Thus did the year one thousand seven hundred and seventy-five conduct their Greatnesses, and myriads of small creatures-the creatures of this chronicle among the rest-along the roads that lay before them.")
// })
// keyboard.startKeyboardService()
// media.startMediaService()
