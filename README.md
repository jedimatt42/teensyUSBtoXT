teensyUSBtoXT
=============

Simple Arduino based USB to XT keyboard converter.

[Project Page](http://ti994a.cwfk.net/UsbGeneve.html)

### Status

Basic, 101-key USB-Keyboard to XT mapping is complete and functioning. 

### About

This uses a Teensy 3.2 microcontroller, and a UHS mini pro ( USB Host Shield mini ) to process incoming usb keyboard interactions and output the XT keyboard signals. 

I've used Teensy 3.1 and 3.2 boards, and the [www.duinofun.com USB mini v2.0.](https://smile.amazon.com/HiLetgo-Development-Compatible-Interface-Arduino/dp/B01EWW9R1E/ref=sr_1_fkmr1_1?keywords=usb+mini+v2.0+host+shield&qid=1574724973&sr=8-1-fkmr1)

The TI 99 USB Keys pcboard can be used. The [schematic](https://github.com/jedimatt42/TI-99-usb-keys/blob/master/schematic.pdf) will work, you just don't need the 15 pins going to the TI-99/4A matrix keyboard.  You don't have to use the pcboard, as there are far fewer wires with this.. But you should review my project page for illustrations on getting the usb host shield to provide +5v to the usb keyboard: [hardware page](http://ti994a.cwfk.net/TiUsbKeys.html)

Chris Schnieder has also developed a pcboard with a 5 Pin DIN jack, so you can just use a 5 Pin DIN patch cable. See -> [here](http://shift838.99er.net/atxtusbkeys.html)

I am targeting my:
  Myarc Geneve 9640 Family Computer.

The XT keyboard write routine was taken from [tinyPS2toXTArduino](https://github.com/kesrut/tinyPS2toXTArduino)
Then modified to follow the pattern in [AT2XT](https://github.com/cr1901/AT2XT)

This can be built using the same hardware as my TI 99 USB Keys adapter. (just output to a XT 5pin DIN instead of simulating the TI-99/4a matrix keyboard)

I am currently connecting to the Geneve 9640's XT keyboard port as follows to the 5 header pins on the usb keyboard adapter pcboard.

```
XT 5 pin din  ->   TI 99 USB Keys adapter board
---------------|-------------------------------
pin 1 - clock  |   G3 - Teensy pin 0
pin 2 - data   |   G2 - Teensy pin 1
pin 4 - Ground |   GND 
pin 5 - +5v    |   +5v 
```

### References 

See [XT Scan Codes Demystified](http://www.quadibloc.com/comp/scan.htm) for encoding details.


### Notes

This might server a general purpose, but I have no XT driven devices beyond my Geneve 9640. I am taking a shortcut, in that the Teensy 3.2 is a 3.3 volt device, but it is 5 volt safe/tolerant. So the output data signals are only +3.3v instead of 5v as they would be from a normal XT keyboard. This is sufficient to drive the logic in my target machine, but might require a logic level shifter for other devices. Or just port the code to an actual 5v microcontroller. The Teensy is a bit of overkill for this application, but I'm comfortable with that.

-M@
