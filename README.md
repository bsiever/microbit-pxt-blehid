
```package
microbit-pxt-blehid=github:bsiever/microbit-pxt-blehid
```

# Bluetooth-HID

This extension allows the micro:bit V2 to act like Bluetooth [Human Interface Devices](https://en.wikipedia.org/wiki/Human_interface_device) (HID).  It currently supports [Keyboard](#keyboard), [Mouse](#mouse), [Media Keys](#media-keys) (play, pause, volume up, etc.), a [Gamepad](#gamepad), and an [Absolute Mouse](absolute-mouse) (puts the mouse at a specific position on the screen).

Not all modules are supported on all devices or operating systems:

* Operating systems with some support
  * Android 11 and later (May work on some Android 9+ devices)
    * Tested on a Galaxy Tab A (8", 2019)
    * Here's the [Android BLE HID support list](https://github.com/raghavk92/Android_Bluetooth_HID_Device_Profile_CompatibilityList/blob/master/device_list.txt), which includes details on HID support for about 120 different Android devices.
  * Windows 10 Pro and later
    * Tested on a Microsoft Surface Pro (5th Gen)
  * iOS: Tested on 15.1
    * According to [Apple Support](https://support.apple.com/en-us/HT204387), the HID Profile is suppported on "iPhone 5s and later, iPad Air and later, and iPod touch (6th generation) and later".
    * Tested on an iPhone 11 Pro
  * macOS:  Tested on 11.4 (Big Sur)
    * Tested on an M1 Air, but it should work on any mac made after 2014 running Big Sur or later
* Modules support on each operating system

| Module         | Windows  | macOS  | Android  | iOS  |
|:---------------|:--------:|:------:|:--------:|:----:|
| Keyboard       | X        | X      | X       | X     |
| Media          | X        | X      | X       |       |
| Mouse          | X        | X      | X       | Note 1 |
| Gamepad        | X        | X      | X       |       |
| Absolute Mouse | X        | X      |         |       |

Note 1: iOS can support mouse control if [AssistiveTouch](#assistivetouch) is enabled.

# Pairing and Programming Quirks

Security is really important for wireless Human Interface Devices, like keyboards.  The Micro:bit's Bluetooth communication goes through a process called "pairing" to ensure data exchanged is secure.  The pairing process works like this:

1. You complete your program and download it to the micro:bit.  Here's an example:
    ```block
    input.onButtonPressed(Button.A, function () {
        keyboard.sendString("Hello Bluetooth HID!")
    })
    keyboard.startKeyboardService()
   ```
2. You a) open bluetooth preferences on the device you want to interact with (a computer, phone, or tablet), b) select the micro:bit that you want to connect to, and c)your phone/computer/tablet may ask if you want to "Pair"  (Some devices, like Macs and PCs assume  you want to "Pair" because you selected the micro:bit).  Here are examples of all three:
    * iOS Connection
    * Windows Connection
    * Android Connection
    * macOS Connection
3. Every time "pairing" happens a new "key" is created to encrypt all future communication.  The micro:bit and the other device will both store the key so they can immediately communicate in the future without going through this pairing process.  For example, if your micro:bit loses power and re-starts, the other device will automatically connect to it without going through the pairing process again.  **Unless the micro:bit's key is destroyed!**

## Re-programming and keys

Reprogramming the micro:bit can cause the micro:bit's version of the key to be destroyed, but the other device (computer/phone/tablet) will still have its copy of the key.  The other device will still try to connect to the micro:bit, but it will ignore any messages from the micro:bit (since the micro:bit doesn't have a key to encrypt communication).  To be able to communicate the devices will have to exchange keys again. You'll need to make the other device (computer/phone/tablet) "forget" the key and then go through the pairing process again.  You also use bluetooth settings to cause devices to forget keys:
    * iOS Forget Pair
    * Windows Forget Pair
    * Android Forget Pair
    * macOS Forget Pair

### ~hint
#### Reprogramming without pairing

In some cases you can reprogram the micro:bit without losing any stored keys.  This is usually possible if you are making small changes in the program (and are working in the same environment: same computer/browser/etc.)

### ~
 # Keyboard

```sig
keyboard.startKeyboardService()
```

Starts the keyboard service.  This must execute in the `start` block.

## Complex Keys

Join with text join

# Mouse

Mouse does stuff.

## AssistiveTouch

Can work in iOS with accessibility features enabled ([Assistive Touch](https://support.apple.com/en-us/HT210546) [here](https://www.macworld.com/article/232969/how-to-use-a-mouse-with-your-ipad-or-iphone.html))

# Media Keys

Yeah...

# Absolute Mouse

macOS and Windows only

# Game Pad

# Programming and Pairing

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
