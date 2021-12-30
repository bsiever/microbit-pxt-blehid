

# Keyboard

## Complex Keys

Join with text join
# Mouse

Mouse does stuff.

Can work in iOS with accessibility features enabled ([Assistive Touch](https://support.apple.com/en-us/HT210546) [here](https://www.macworld.com/article/232969/how-to-use-a-mouse-with-your-ipad-or-iphone.html))
# Media

Yeah...

# Absolute Mouse

macOS and Windows only

# Game Pad
# Pairing and Programming Quirks


# Supported Platforms and quirks

* [Android BLE HID support list](https://github.com/raghavk92/Android_Bluetooth_HID_Device_Profile_CompatibilityList/blob/master/device_list.txt)


# Programming and Pairing

# blehid

```package
pins=github:bsiever/microbit-pxt-blehid
```



# Cool Ideas

## Accelerometer Mouse

## Computer / Phone Media Remote

## iOS Camera Release

Trick: Use volume up/down

## iOS Screen Keyboard

Use the Media Eject

# Limitations

## iOS 

* iOS doesn't support a mouse (well, does with assistive touch)
* iOS only supports gamepad with assistive touch
* iOS Doesn't honor media "Stop"



General details on HID [here](https://support.apple.com/en-us/HT204387).  Highlights: "iPhone 5s and later, iPad Air and later, and iPod touch (6th generation) and later".

Hmmm... https://support.apple.com/en-us/HT210414



# Setting the pins

```sig
pins.setI2CPins(sda : DigitalPin,  scl : DigitalPin) : void
```

Set the Data and Clock pins.

<script src="https://makecode.com/gh-pages-embed.js"></script>
<script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
