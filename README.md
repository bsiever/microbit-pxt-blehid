
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

# Keyboard

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
* Use the micro:bit to take pictures and start/stop recordings on your phone/tablet.  Hint: most mobile devices' camera app will take a picture when a volume button is pressed.
* Make a remote control to play/pause music and/or control volume.

## iOS Screen Keyboard

Use the Media Eject

# Limitations

## iOS

* iOS doesn't support a mouse (well, does with assistive touch)
* iOS only supports gamepad with assistive touch
* iOS Doesn't honor media "Stop"

Hmmm... https://support.apple.com/en-us/HT210414

<script src="https://makecode.com/gh-pages-embed.js"></script>
<script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
