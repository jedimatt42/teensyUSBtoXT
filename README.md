teensyUSBtoXT
=============

Simple Arduino based USB to XT keyboard converter.

This uses a Teensy 3.2 microcontroller, and a UHS mini pro ( USB Host Shield mini ) to process incoming usb keyboard interactions and output the XT keyboard signals. 

I am targeting my:
  Myarc Geneve 9640 Family Computer.

The XT keyboard write routine was taken from [tinyPS2toXTArduino](https://github.com/kesrut/tinyPS2toXTArduino)
Then modified to follow the pattern in [AT2XT](https://github.com/cr1901/AT2XT)

This will be built using the same hardware as my TI 99 USB Keys adapter. (just output to a XT 5pin DIN instead of simulating the TI-99/4a matrix keyboard)

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

This might server a general purpose, but I have no XT driven devices beyond my Geneve 9640. I am taking a shortcut, in that the Teensy 3.2 is a 3.3 volt device, but it is 5 volt safe/tolerant. So the output data signals are only +3.3v instead of 5v as they would be from a normal XT keyboard. This is sufficient to drive the logic in my target machine, but might require a logic level shifter for other devices. Or just port the code to an actual 5v microcontroller. The Teensy is a bit of overkill for this application.

### Issues

I did not implement any buffering yet in the adapter. XT keyboards typically have a small buffer. Presently you must type slowly enough for this to work. I will implement a small buffer to combat that, as well as attempt to improve the output frequency.

I have not paid any attention to caps-lock and other lock keys as of yet. 

Some XT keys are horribly complex when using a 101-key style keyboard. They have to change numlock state and act like the numpad keys, and then restore numlock state. 

I'm having trouble comprehending what the reference material says to do with Pause,Break,Print Screen and SysRq. But I'll figure it out. 

