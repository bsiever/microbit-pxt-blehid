# blehid

```package
blehid=github:bsiever/microbit-pxt-blehid
```

This extension allows the micro:bit V2 to be Bluetooth [Human Interface Devices](https://en.wikipedia.org/wiki/Human_interface_device) (HID).  It currently supports services for [Keyboard](#keyboard), [Mouse](#mouse), [Media Keys](#media-keys) (play, pause, volume up, etc.), a [Gamepad](#gamepad), and an [Absolute Mouse](absolute-mouse) (puts the mouse at a specific position on the screen).

Not all services are supported on all devices or operating systems. Operating systems with some support

* Android 11 and later (May work on some Android 9+ devices)
  * Tested on a Galaxy Tab A (8", 2019)
  * Here's the [Android BLE HID support list](https://github.com/raghavk92/Android_Bluetooth_HID_Device_Profile_CompatibilityList/blob/master/device_list.txt), which includes details on HID support for about 120 different Android devices.
* Windows 10 Pro and later
  * Tested on a Microsoft Surface Pro (5th Gen)
* iOS: Tested on 15.1
  * According to [Apple Support](https://support.apple.com/en-us/HT204387), the HID Profile is supported on "iPhone 5s and later, iPad Air and later, and iPod touch (6th generation) and later".
  * Tested on an iPhone 11 Pro
* macOS:  Tested on 11.4 (Big Sur)
  * Tested on an M1 Air, but it should work on any mac made after 2014 running Big Sur or later

 Service support on each operating system <br />

>  | Service         | Windows  | macOS  | Android | iOS |
>  |:---------------|:--------:|:------:|:--------:|:----:|
>  | Keyboard       | X        | X      | X       | X     |
>  | Media          | X        | X      | X       |       |
>  | Mouse          | X        | X      | X       | Note 1 |
>  | Gamepad        | X        | X      | X       |       |
>  | Absolute Mouse | X        | X      |         |       | 
>  | 
>
> Note 1: iOS can support mouse control if [AssistiveTouch](#assistivetouch) is enabled.

# Pairing and Programming Quirks

Security is really important for wireless Human Interface Devices, like keyboards.  The Micro:bit's Bluetooth communication goes through a process called "pairing" to ensure data exchanged is secure.  The pairing process works like this:

1. You complete your program and download it to the micro:bit.  Here's an example:

> ```blocks
> input.onButtonPressed(Button.A, function () {
>     keyboard.sendString("Hello Bluetooth HID!")
> })
> keyboard.startKeyboardService()
> ```
2. You a) open bluetooth preferences on the device you want to interact with (a computer, phone, or tablet), b) select the micro:bit that you want to connect to, and c)your phone/computer/tablet may ask if you want to "Pair"  (Some devices, like Macs and PCs assume  you want to "Pair" because you selected the micro:bit).  Here are examples of all three:
    * iOS Connection
    * Windows Connection
    * Android Connection
    * macOS Connection

https://user-images.githubusercontent.com/1421446/149054357-aed2a475-ddfb-4786-8f2d-72e843a1811f.mp4

3. Every time pairing happens a new "key" is created to encrypt all future communication.  The micro:bit and the other device will both store the key so they can immediately communicate in the future without going through this pairing process.  For example, if your micro:bit loses power and re-starts, the other device will automatically connect to it without going through the pairing process again.  **Unless the micro:bit's key is destroyed!**

## Re-programming and keys

Reprogramming the micro:bit can cause the micro:bit's version of the key to be destroyed, but the other device (computer/phone/tablet) will still have its copy of the key.  The other device will still try to connect to the micro:bit, but it will ignore any messages from the micro:bit (since the micro:bit doesn't have a key to encrypt communication).  To be able to communicate the devices will have to exchange keys again. You'll need to make the other device (computer/phone/tablet) "forget" the key and then go through the pairing process again.  You also use bluetooth settings to cause devices to forget keys:
> * iOS Forget Pair
> * Windows Forget Pair
> * Android Forget Pair
> * macOS Forget Pair

### ~hint
#### Reprogramming without pairing

If you are just making small changes to an already-paired micro:bit soon after you completed pairing (and using the same computer/browser), you can usually reprogram if without losing the stored key. 

### ~

# Keyboard API

## Starting the Keyboard Service #keyboard-startKeyboardService

```sig
keyboard.startKeyboardService()
```

Starts the keyboard service.  This must execute in the `start` block.  All other keyboard blocks require the service is started. 

## Sending keystrokes #keyboard-sendString

```sig
keyboard.sendString()
```

Send a sequence of characters one-at-a-time.  For example, ``[keyboard.sendString('Hello Keyboard!')]`` is equivalent to typing the individual letters one-at-a-time.

## Special Keys #keyboard-keys


```sig
keyboard.keys()
```

Keys that can't be typed in strings.  To simulate pressing enter ``[keyboard.sendString(keyboard.keys(keyboard._Key.enter))]``

These can be combined with typed characters by joining them together: ``[keyboard.sendString('Hello Keyboard!'+keyboard.keys(keyboard._Key.enter))]``

## Key Modifiers #keyboard-modifiers

```sig
keyboard.modifiers()
```

Modifiers are keys like Control, or Alt, or the Windows key on a PC / Command key on a Mac. Modifiers modify another key and are 
often used for special commands.  Pressing Control and "S" is often used to save files (Command and "S" on Macs).  You can send 
a "Contrl+S" by joining the Control modifier: ``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.control) + "s")]``.  
The Modifier modifies the first character joined after the "+".  For example, ``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.control) + "stop")]`` would send "Contrl+s" and then sent "t", "o", and finally "p". 

Some command require multiple modifiers, which can also be joined with the Text join.  All the modifiers in a series add to the first non-modifier ``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.control) + keyboard.modifiers(keyboard._Modifier.alt) + keyboard.keys(keyboard._Key.delete))]``

It's also possible to send a sequence of modified keys.  For example, on Macs Command and "c" copy and Command and "c" paste. A copy/paste/paste could be done by:
``[keyboard.sendString("" + keyboard.modifiers(keyboard._Modifier.apple) + "c" + keyboard.modifiers(keyboard._Modifier.apple) + "v" + keyboard.modifiers(keyboard._Modifier.apple) + "v")
]``

## Sending several simultaneously pressed keys #keyboard-sendSimultaneousKeys

```sig
keyboard.sendSimultaneousKeys()
```

This command is in the "... more" palette of advanced commands.  It allows up to 6 keys can be sent at the same time. This is like smashing down keys at the exact same time. The "+" on the block can 
be expanded to give additional control over when keys are released.  For example, while playing a video game you may want to hold down on the right arrow to move right: ``[keyboard.sendSimultaneousKeys(keyboard.keys(keyboard._Key.right), true)]``.

At some point you may also want to simulate pushinng the space bar to jump while still moving to the right: ``[keyboard.sendSimultaneousKeys("" + keyboard.keys(keyboard._Key.right) + " ", true)]``

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

HID keyboards send "scancodes" that represent keys.  You may want to send keys that aren't covered here, like the Function Keys (F1, etc.). 
 You can do this by sending the scancode for the key.  Supported scancodes can be found on page 83 of the 
 "[HID Usage Tables for Universal Serial Bus (USB) v 1.21](https://usb.org/sites/default/files/hut1_21.pdf#page=83)".  If you look up Keyboard F1 
 in the table (page 83) you'll find it has a scancode of 112 (in the AT-101 column of the table). To send an F1: ``[keyboard.sendString(keyboard.rawScancode(112))]`` 

## Detecting if the keyboard service use has changed #keyboard-setStatusChangeHandler

```sig 
keyboard.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event hander will indicate that the status of the subscription has changed (either 
the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the keyboard service may be in use #keyboard-isEnabled

```sig 
keyboard.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off our out of range. 

# Media Keys 

## Starting the Media Service #media-startMediaService

```sig
media.startMediaService()
```

Starts the media service.  This must execute in the `start` block.  All other media blocks require the service is started. 

## Specific Media Keys #media-keys

```sig
media.keys(media._MediaKey.next)
```

Select a specific media key to send (only the keys listed may be sent).

## Sending a media key #media-sendCode

```sig
media.sendCode()
```

Send a media key.  For example, to send "Play/pause" ``[media.sendCode(media.keys(media._MediaKey.playPause))]`` 

### ~hint
#### Showing the iOS Keyboard with Keyboard Service

When the regular [Keyboard](#keyboard) service is used with iOS it will disable use of the on-screen keyboard.  You can re-enable 
it by sending an eject: ``[media.sendCode(media.keys(media._MediaKey.eject))]``
### ~


## Detecting if the media service use has changed #media-setStatusChangeHandler

```sig 
media.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event hander will indicate that the status of the subscription has changed (either 
the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the media service may be in use #media-isEnabled


```sig 
media.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off our out of range. 


# Mouse

## Starting the Mouse Service #mouse-startMouseService


```sig
mouse.startMouseService()
```

Starts the mouse service.  This must execute in the `start` block.  All other mous blocks require the service is started. 


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

Send all mouse behavior simultaneously.  `x` is the amount to move horizontaly (-127 to 127), `y` is the amount to move vertically (-127 to 127), 
`left` indicates if the left mouse button is pressed, `middle` indicates if the middle mouse button is pressed, `right` indicates if the right 
mouse button is pressed, `scroll` is the amount to scroll (-127 to 127), and `hold` indicates if the buttons should be "held" until the next mouse command (when `false` 
the buttons are "clicked").

## Detecting if the mouse service use has changed #mouse-setStatusChangeHandler

```sig 
mouse.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event hander will indicate that the status of the subscription has changed (either 
the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the mouse service may be in use #mouse-isEnabled

```sig 
mouse.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off our out of range. 

## AssistiveTouch

A mouse can be used in iOS when ([Assistive Touch](https://support.apple.com/en-us/HT210546) features are enabled,  See [here](https://www.macworld.com/article/232969/how-to-use-a-mouse-with-your-ipad-or-iphone.html) for more detail.

# Absolute Mouse

Absolute mouse currently only works on macOS and Windows.  Interactions beteen Absolute Mouse and Mouse may not be well defined. 

## Starting the Absolute Mouse Service #absmouse-startAbsoluteMouseService

```sig
absmouse.startAbsoluteMouseService()
```

Starts the Absolute Mouse service.  This must execute in the `start` block.  All other Absolute Mouse blocks require the service is started. 

```sig
absmouse.movexy()
```
Move the mouse pointer to the specific location.  x goes from -32767 to 32767.  -32767 represents the left side of the screen and 32767 represents the right side of the screen.  y goes from -32767 to 32767.  -32767 represents the top of the screen and 32767 represents the bottom of the screen. (0,0)
 is the center of the screen. 

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

`x` is the horizontal location to place the mouse (-32767 to 32767), `y` is the vertical location to place the mouse (-32767 to 327679),
`left` indicates if the left mouse button is pressed, `middle` indicates if the middle mouse button is pressed, `right` indicates if the right 
mouse button is pressed,  and `hold` indicates if the buttons should be "held" until the next mouse command (when `false` 
the buttons are "clicked").

## Detecting if the absmouse service use has changed #absmouse-setStatusChangeHandler

```sig 
absmouse.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event hander will indicate that the status of the subscription has changed (either 
the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the absmouse service may be in use #absmouse-isEnabled

```sig 
absmouse.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off our out of range. 


# Game Pad

## Starting the Gamepad Service #gamepad-startGamepadService

```sig
gamepad.startGamepadService()
```

Starts the Gamepad service.  This must execute in the `start` block.  All other Gamepad blocks require the service is started. 

## Direction Pad keys (D-Pad) #gamepad-_dpad 

```sig
gamepad._dpad(GameDirection.noDirection)
```

TODO

## Buttons #gamepad-_buttons 

```sig 
gamepad._buttons()

```

TODO

## Send a gamepad command #gamepad-send

```sig 
gamepad.send()
```

TODO


## Detecting if the gamepad service use has changed #gamepad-setStatusChangeHandler

```sig 
gamepad.setStatusChangeHandler()
```

The device using the service needs to "subscribe" to the service.  This event hander will indicate that the status of the subscription has changed (either 
the other device has subscribed or unsubscribed).  This is an indicator that the device is "listening" to your code.  However, it isn't perfect.  Some operating systems, like Android, subscribe to every service whether they use it or not.

## Detecting if the gamepad service may be in use #gamepad-isEnabled

```sig 
gamepad.isEnabled()
```

`true` indicates that the device is currently subscribed to the service.  `false` indicates the device is _not_ currently subscribed to the service. This may mean that the other device is off our out of range. 

# Cool Ideas / Challenges

* Create a mouse using the accelerometer
* Create a gamepad using the accelerometer
* Use the keyboard support to control a slideshow (Google Slides, PowerPoint, Keynote, etc.)
* Use the micro:bit to take pictures and start/stop recordings on your phone/tablet.  Hint: most mobile devices' camera app will take a picture when a volume button is pressed
* Make a remote control to play/pause music and/or control volume
* Automate repetitive tasks

## iOS Screen Keyboard

Use the Media Eject to allow the keyboard to be used while also using the Keyboar service.

# Limitations

## iOS

* iOS doesn't support a mouse (well, does with assistive touch)
* iOS only supports gamepad with assistive touch
* iOS Doesn't honor media "Stop"

Hmmm... https://support.apple.com/en-us/HT210414

<script src="https://makecode.com/gh-pages-embed.js"></script>
<script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
