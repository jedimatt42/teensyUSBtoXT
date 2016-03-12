#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

// Reboot support
#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

#define NUMLOCK_STARTUP true
#define CAPSLOCK_STARTUP false
#define SCROLLLOCK_STARTUP false

#include "UsbKbdRptParser.h"
#include "xt_keyboard.h"

USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

UsbKbdRptParser Prs;

long lastGoodState;
long firstBoot;

void setup()
{
  xt_setup();

  firstBoot = lastGoodState = millis();
  
  // Wait for keyboard to be up
  while (Usb.Init() == -1)
    delay( 20 );

  HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
}

void loop()
{
  // Read USB input which updates the state of the in-memory keyboard matrix.
  Usb.Task();

  long loopMillis = millis();
  uint8_t state = Usb.getUsbTaskState();
  
  if (state != USB_STATE_RUNNING) {
    long rightnow = loopMillis;
    if ( (rightnow - lastGoodState) > 5000 ) {
      CPU_RESTART;
    }
  } else {
    lastGoodState = loopMillis;
    if (firstBoot != 0) {
      // Set numlock and capslock on, leave scroll lock off.
      Prs.setKeyLocks(&HidKeyboard, NUMLOCK_STARTUP, CAPSLOCK_STARTUP, SCROLLLOCK_STARTUP);
      firstBoot = 0; 
    }
  }

  xt_loop();
}

