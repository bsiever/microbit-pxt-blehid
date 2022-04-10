# blehid

```package
blehid=github:bsiever/microbit-pxt-blehid
```

This extension allows the micro:bit V2 to act like a [Human Interface Devices](https://en.wikipedia.org/wiki/Human_interface_device) (HID) over Bluetooth.  It currently supports services for [Keyboard](#keyboard), [Mouse](#mouse), [Media Keys](#media-keys) (play, pause, volume up, etc.), a [Gamepad](#gamepad), and an [Absolute Mouse](absolute-mouse) (puts the mouse at a specific position on the screen).

See [Cool Ideas and Challenges](#cool-ideas-and-challenges) for some examples of how this extension can be used.

Not all services are supported on all devices or operating systems. Operating systems with some support are:

* Android 11 and later (May work on some Android 9+ devices)
  * Tested on a Galaxy Tab A (8", 2019)
  * Here's an unofficial [Android BLE HID support list](https://github.com/raghavk92/Android_Bluetooth_HID_Device_Profile_CompatibilityList/blob/master/device_list.txt), which includes details on HID support for about 120 different Android devices.
* Windows 10 Pro and later
  * Tested on a Microsoft Surface Pro (5th Gen)
* iOS: Tested on 15.1
  * According to [Apple Support](https://support.apple.com/en-us/HT204387), the HID Profile is supported on "iPhone 5s and later, iPad Air and later, and iPod touch (6th generation) and later".
  * Tested on an iPhone 11 Pro
* macOS:  Tested on 11.4 (Big Sur)
  * Tested on an M1 Air, but it should work on any Mac made after 2014 running Big Sur or later

You are welcome to use the Extensions's discussions forum to share any new/different platforms that work or don't:
* [List of working devices](https://github.com/bsiever/microbit-pxt-blehid/discussions/21)
* [List of *NON*-working devices](https://github.com/bsiever/microbit-pxt-blehid/discussions/23)
* [All discussions](https://github.com/bsiever/microbit-pxt-blehid/discussions)

Not all features are supported on each operating system: <br />

| Service         | Windows  | macOS  | Android | iOS   |
|:---------------|:--------:|:------:|:--------:|:-----:|
| Keyboard       | X        | X      | X       | X      |
| Media          | X        | X      | X       |        |
| Mouse          | X        | X      | X       | Note 1 |
| Gamepad        | X        | X      | X       |        |
| Absolute Mouse | X        | X      |         | &nbsp; |

Note 1: iOS can support mouse control if [AssistiveTouch](#assistivetouch) is enabled.

# Pairing and Programming Quirks

Security is important for wireless Human Interface Devices, like keyboards.  The Micro:bit's Bluetooth communication goes through a process called "pairing" to ensure data exchanged is secure.  The pairing process works like this:

## 1. Program the micro:bit

Here's an example program:

```blocks
input.onButtonPressed(Button.A, function () {
    keyboard.sendString("Hello Bluetooth HID!")
})
keyboard.startKeyboardService()
```

Notice that it starts a service in the ```start```.

## 2. Have your device connect to the micro:bit

1. Open bluetooth preferences on the device you want to interact with (a computer, phone, or tablet),
2. select the micro:bit that you want to connect to (it will be named something like "uBit [XXXXX]"), and
3. your phone/computer/tablet may ask if you want to "Pair"  (Some devices, like Macs and PCs assume  you want to "Pair" because you selected the micro:bit).  

Every time pairing happens a new "key" is created to encrypt all future communication.  The micro:bit and the other device will both store the key so they can immediately communicate in the future without going through this pairing process.  For example, if your micro:bit loses power and re-starts, the other device will automatically connect to it without going through the pairing process again.  However, sometimes changes to your program will cause the micro:bit's key to be destroyed! (See [Re-programming and keys](#re-programming-and-keys))

Here are examples of all three steps on each operating system:

### iOS Pairing

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149055788-594206e2-3ec7-477f-8c7f-28380c855a23.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149055788-594206e2-3ec7-477f-8c7f-28380c855a23.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.
###  macOS Pairing

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149054357-aed2a475-ddfb-4786-8f2d-72e843a1811f.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149054357-aed2a475-ddfb-4786-8f2d-72e843a1811f.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.

### Android Pairing

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149252209-67c847b2-aa58-4785-869f-91105304ef8f.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149252209-67c847b2-aa58-4785-869f-91105304ef8f.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.

### Windows Pairing

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149252173-0dd6ebf0-fa2b-4070-8c2c-92288513195c.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149252173-0dd6ebf0-fa2b-4070-8c2c-92288513195c.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.


## Re-programming and keys

Reprogramming the micro:bit can cause the micro:bit's version of the key to be destroyed, but the other device (computer, phone, tablet, etc.) will still have its copy of the key.  The other device will still try to connect to the micro:bit, but then it will ignore any commands from the micro:bit since the micro:bit doesn't have a valid key.  To be able to communicate the devices will have to exchange keys again. You'll need to make the other device (computer, phone, tablet, etc.) "forget" the key and then go through the pairing process again.  You also use bluetooth settings to cause devices to forget keys (un-pair). 

Here are examples of unpairing on each operating system:

### iOS Un Pair

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149056052-7e46139f-718e-443a-a550-fae258d8e9c2.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149056052-7e46139f-718e-443a-a550-fae258d8e9c2.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.

### macOS Un Pair

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149055265-510663ac-4243-4d7d-a922-9b40f27a1d3a.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149055265-510663ac-4243-4d7d-a922-9b40f27a1d3a.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.

### Android Un Pair

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149252273-4bd5c3ae-7389-4ef5-ac34-43e34076cbaf.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149252273-4bd5c3ae-7389-4ef5-ac34-43e34076cbaf.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.

### Windows Un Pair

<video width="320" height="240" controls>
  <source src="https://user-images.githubusercontent.com/1421446/149252110-cc18c5ba-0cdd-4823-af8b-047f2a683a6d.mp4" type="video/mp4">
</video>

https://user-images.githubusercontent.com/1421446/149252110-cc18c5ba-0cdd-4823-af8b-047f2a683a6d.mp4

In the video the micro:bit's bluetooth name is "BBC micro:bit". Yours will be named something like "uBit [XXXXX]", where "XXXXX" will be the unique name of your micro:bit.

### ~hint
#### Reprogramming without pairing

If you are just making small changes to a paired micro:bit, you can usually reprogram if without losing the stored key.

### ~

# Keyboard Service #keyboard

## Starting the Keyboard Service #keyboard-startKeyboardService

```sig
keyboard.startKeyboardService()
```

Starts the keyboard service.  This must execute in the `start` block.  All other keyboard blocks require the service be started.

### ~hint
#### Showing the iOS Keyboard with Keyboard Service

When the regular [Keyboard](#keyboard) service is used with iOS it will disable use of the on-screen keyboard.  You can re-enable it by sending an ``eject`` with the [`media service`](#media)
### ~

## Sending keystrokes #keyboard-sendString

```sig
keyboard.sendString()
```

Send a sequence of characters one-at-a-time.  For example, ``[keyboard.sendString('Hello Keyboard!')]`` is equivalent to typing the individual letters one-at-a-time.

## Special Keys #keyboard-keys

```sig
keyboard.keys()
```

Keys that can't be typed in strings.  To simulate pressing enter send ``enter``, like: ``[keyboard.sendString(keyboard.keys(keyboard._Key.enter))]``

These can be combined with typed characters by joining them together: ``[keyboard.sendString('Hello Keyboard!'+keyboard.keys(keyboard._Key.enter))]``

## Key Modifiers #keyboard-modifiers

```sig
keyboard.modifiers()
```

Modifiers are keys like Control, or Alt, the Windows key on a PC, or the Command key on a Mac. Modifiers modify another key and are often used for special commands.  For example, pressing Control and "S" is often used to save files (Command and "S" on Macs).  You can send a "Control+S" by joining the Control modifier to ``"s"``: ``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.control) + "s")]``.  The Modifier modifies the first character joined after the "+".  For example, ``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.control) + "stop")]`` would send "Contrl+s" and then send "t", "o", and finally "p".

Some commands require multiple modifiers, which can also be joined.  All the modifiers in a series add to the first non-modifier. For example, simultaneously pressing Control and Alt and the ``delete`` key can be done via: ``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.control) + keyboard.modifiers(keyboard._Modifier.alt) + keyboard.keys(keyboard._Key.delete))]``

It's also possible to send a sequence of modified keys.  For example, on Macs Command with "c" copies items and Command with "v" pastes a copied items. A copy/paste/paste could be done by:
``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.apple) + "c" + keyboard.modifiers(keyboard._Modifier.apple) + "v" + keyboard.modifiers(keyboard._Modifier.apple) + "v")
]``

## Sending several simultaneously pressed keys #keyboard-sendSimultaneousKeys

```sig
keyboard.sendSimultaneousKeys()
```

This command is in the "... more" palette of advanced commands.  It allows up to 6 simultaneous keys to be sent at the same time. This is like smashing down keys at the exact same time. The "+" on the block can be expanded to give additional control over when keys are released.  For example, while playing a video game you may want to hold down on the right arrow to move right: ``[keyboard.sendSimultaneousKeys(keyboard.keys(keyboard._Key.right), true)]``.

At some point you may also want to simulate pushing the space bar to jump while still moving to the right: ``[keyboard.sendSimultaneousKeys("" + keyboard.keys(keyboard._Key.right) + " ", true)]``

Finally, you may want to release all the keys: ``[keyboard.releaseKeys()]``

## Releasing any "held" keys #keyboard-releaseKeys

```sig
keyboard.releaseKeys()
```

Release any keys that were held down by use of ``[keyboard.sendSimultaneousKeys("...", true)]``

## Raw scancodes for additional keys #keyboard-rawScanCode

```sig
keyboard.rawScancode()
```

HID keyboards send "scancodes" that represent keys.  You may want to send keys that aren't covered here, like the Function Keys (F1, etc.). You can do this by sending the scancode for the key.  Supported scancodes can be found starting on page 83 of the "[HID Usage Tables for Universal Serial Bus (USB) v 1.21](https://usb.org/sites/default/files/hut1_21.pdf#page=83)".  If you look up Keyboard F1 in the table, you'll find it has a scancode of 112 (in the AT-101 column of the table). So, to send an F1: ``[keyboard.sendString(keyboard.rawScancode(112))]``

## Detecting if the keyboard service use has changed #keyboard-setStatusChangeHandler

```sig
keyboard.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event handler will indicate that the status of the subscription has changed (either the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the keyboard service may be in use #keyboard-isEnabled

```sig
keyboard.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off or out of range.

# Media Service #media 

## Starting the Media Service #media-startMediaService

```sig
media.startMediaService()
```

Starts the media service.  This must execute in the `start` block.  All other media blocks require the service be started.

## Specific Media Keys #media-keys

```sig
media.keys(media._MediaKey.next)
```

Select a specific media key to send. Only the keys listed may be sent.

## Sending a media key #media-sendCode

```sig
media.sendCode()
```

Send a media key.  For example, to send "play/pause" ``[media.sendCode(media.keys(media._MediaKey.playPause))]`` 

### ~hint
#### Showing the iOS Keyboard with Keyboard Service

When the regular [Keyboard](#keyboard) service is used with iOS it will disable use of the on-screen keyboard.  You can re-enable it by sending an eject: ``[media.sendCode(media.keys(media._MediaKey.eject))]``
### ~

## Detecting if the media service use has changed #media-setStatusChangeHandler

```sig
media.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event handler will indicate that the status of the subscription has changed (either the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the media service may be in use #media-isEnabled

```sig
media.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off or out of range.

# Mouse Service #mouse

## Starting the Mouse Service #mouse-startMouseService

```sig
mouse.startMouseService()
```

Starts the mouse service.  This must execute in the `start` block.  All other mouse blocks require the service be started.

```sig
mouse.movexy()
```

Move the mouse by the given amounts in the x (horizontal) and y (vertical) directions.  x can be from -127 to 127.  y can be from -127 to 127.

```sig
mouse.click()
```

Click the left mouse button.

```sig 
mouse.middleClick()
```

Click the middle mouse button.


```sig 
mouse.rightClick()
```

Click the right mouse button.

```sig 
mouse.scroll()
```

Scroll the scroll wheel by the given number of "clicks".  The clicks can be from -127 to 127. 

```sig 
mouse.send()
```

Send all mouse behavior simultaneously.  `x` is the amount to move horizontaly (-127 to 127), `y` is the amount to move vertically (-127 to 127), `left` indicates if the left mouse button is pressed, `middle` indicates if the middle mouse button is pressed, `right` indicates if the right mouse button is pressed, `scroll` is the amount to scroll (-127 to 127), and `hold` indicates if the buttons should be "held" until the next mouse command (when `false` the buttons are "clicked").

## Detecting if the mouse service use has changed #mouse-setStatusChangeHandler

```sig 
mouse.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event handler will indicate that the status of the subscription has changed (either the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the mouse service may be in use #mouse-isEnabled

```sig 
mouse.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off or out of range.

### ~hint
#### iOS AssistiveTouch

A mouse can be used in iOS when [AssistiveTouch](https://support.apple.com/en-us/HT210546) features are enabled,  See [here](https://www.macworld.com/article/232969/how-to-use-a-mouse-with-your-ipad-or-iphone.html) for more detail.
### ~


# Absolute Mouse Service #absolute-mouse

Absolute mouse currently only works on macOS and Windows.  Interactions beteen Absolute Mouse and Mouse may not be well defined.

## Starting the Absolute Mouse Service #absmouse-startAbsoluteMouseService

```sig
absmouse.startAbsoluteMouseService()
```

Starts the absolute mouse service.  This must execute in the `start` block.  All other absolute mouse blocks require the service be started.

```sig
absmouse.movexy()
```

Move the mouse pointer to the specific location.  x goes from -32767 to 32767.  -32767 represents the left side of the screen and 32767 represents the right side of the screen.  y goes from -32767 to 32767.  -32767 represents the top of the screen and 32767 represents the bottom of the screen. (0,0) is the center of the screen.

### ~hint 
#### Screen coordinates and mapping

You can:
* Identify the resolution of your screen (Ex: 2560x1600)
* Measure the distance over and down to something you want to interact with as well as the total screen width and height. 
* Use the above to compute the approximate coordinates of an item on the sceen
* Take advantage of the `map` block (``[y=Math.map(0,0,0,0,0)]``) to convert from the desired screen coordinate to the absolute mouse coordinate.

For example, if:
* Screen is 28cm wide and 2560 pixels horizontal resolution
* The item you want to click on the screen is 6cm from the left

The x coordinate is approximately: 6cm/28cm*2560pix = 548pix

The absolute y coordinate can be computed by: ``[y=Math.map(548,0,2560,-32767,32767)]``


### ~

```sig
absmouse.click()
```

Click the left mouse button.

```sig
absmouse.middleClick()
```

Click the middle mouse button.

```sig
absmouse.rightClick()
```

Click the right mouse button.

```sig
absmouse.send()
```

Send all absolute mouse behavior simultaneously.  x: number, y: number, left: boolean, middle: boolean, right: boolean, hold: boolean): void;

`x` is the horizontal location to place the mouse (-32767 to 32767), `y` is the vertical location to place the mouse (-32767 to 327679),`left` indicates if the left mouse button is pressed, `middle` indicates if the middle mouse button is pressed, `right` indicates if the right mouse button is pressed,  and `hold` indicates if the buttons should be "held" until the next mouse command (when `false` the buttons are "clicked").

## Detecting if the absmouse service use has changed #absmouse-setStatusChangeHandler

```sig
absmouse.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event handler will indicate that the status of the subscription has changed (either the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the absmouse service may be in use #absmouse-isEnabled

```sig
absmouse.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off or out of range.

# Gamepad Service #gamepad-service

## Starting the Gamepad Service #gamepad-startGamepadService

```sig
gamepad.startGamepadService()
```

Starts the gamepad service.  This must execute in the `start` block.  All other gamepad blocks require the service be started.

## Direction Pad keys (D-Pad) #gamepad-_dpad

```sig
gamepad._dpad(GameDirection.noDirection)
```

A direction value for the direction pad

## Buttons #gamepad-_buttons 

```sig
gamepad._buttons()

```

A value indicating if a designated button is pressed or not. 

## Send a gamepad command #gamepad-send

```sig
gamepad.send()
```

Send all gamepad behavior simultaneously.  `buttons` is a set of buttons and their current state, `x` is the amount to move horizontally (-127 to 127), `y` is the amount to move vertically (-127 to 127), `dpad` is the value of the direction pad, `z` is the amount to move on the z-axis (-127 to 127), `rx` is the rotation about the x-axis.

## Detecting if the gamepad service use has changed #gamepad-setStatusChangeHandler

```sig
gamepad.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event handler will indicate that the status of the subscription has changed (either the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the gamepad service may be in use #gamepad-isEnabled

```sig
gamepad.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off or out of range.

# Cool Ideas and Challenges

Here are some examples: [https://youtu.be/n4J5GN72N_4](https://youtu.be/n4J5GN72N_4)

* Create a mouse using the accelerometer
* Create a gamepad using the accelerometer
* Use the keyboard support to control a slideshow (Google Slides, PowerPoint, Keynote, etc.)
* Use the micro:bit to take pictures and start/stop recordings on your phone/tablet.  Hint: most mobile devices' camera app will take a picture when a volume button is pressed
* Make a remote control to play/pause music and/or control volume
* Automate repetitive computer tasks

# Tips

## iOS Screen Keyboard

Use the Media Eject to allow the keyboard to be used while also using the Keyboard service.

# Known Limitations

## Windows

* You may need an application to "remap" the GamePad controls provided by this extension to work with a specific game.

## macOS

* You may need an application to "remap" the GamePad controls provided by this extension to work with a specific game. Applications like [Joystick Monitor](https://apps.apple.com/us/app/joystick-monitor/id1361339902?mt=12) can help test if/how the GamePad is detected.

## iOS

* Doesn't support a mouse or gamepad unless [AssistiveTouch](#assistivetouch) is enabled
* Doesn't honor media "Stop"
* Doesn't support `Absolute Mouse`

## Android

* Doesn't support `Absolute Mouse`

## Misc Links & References

- I develop micro:bit extensions in my spare time to support activities I'm enthusiastic about, like summer camps and science curricula.  You are welcome to become a sponsor of my micro:bit work (one time or recurring payments), which helps offset equipment costs: [here](https://github.com/sponsors/bsiever). Any support at all is greatly appreciated!

<script src="https://makecode.com/gh-pages-embed.js"></script>
<script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
