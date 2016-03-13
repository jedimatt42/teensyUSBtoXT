teensyUSBtoXT
=============

Simple Arduino based USB to XT keyboard converter.

### Status

Basic, 101-key USB-Keyboard to XT mapping is complete and functioning. 

### About

This uses a Teensy 3.2 microcontroller, and a UHS mini pro ( USB Host Shield mini ) to process incoming usb keyboard interactions and output the XT keyboard signals. 

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
