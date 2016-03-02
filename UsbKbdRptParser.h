#ifndef _USB_KBD_RPT_PARSER_H
#define _USB_KBD_RPT_PARSER_H

#include <hidboot.h>

#include "USBCodes.h"
#include "XTCodes.h"

//-----------------------------------------------
// USB Keyboard input handling - mostly taken
//   from the USB Host Boot Keyboard example.

class UsbKbdRptParser : public KeyboardReportParser
{
  protected:
    virtual void OnControlKeysChanged(uint8_t before, uint8_t after);
    virtual void OnKeyDown	(uint8_t mod, uint8_t key);
    virtual void OnKeyUp	(uint8_t mod, uint8_t key);

  private:
    void updateModifier(uint8_t mask, uint8_t before, uint8_t after, byte* xtkey);

  public:
    UsbKbdRptParser();
    void setKeyLocks(HID* hid, boolean numLock, boolean capsLock, boolean scrollLock);
};

UsbKbdRptParser::UsbKbdRptParser()
{
}

void UsbKbdRptParser::setKeyLocks(HID* hid, boolean numLock, boolean capsLock, boolean scrollLock)
{ 
  if (numLock) {
    kbdLockingKeys.kbdLeds.bmNumLock = 1;
  }
  if (capsLock) {
    kbdLockingKeys.kbdLeds.bmCapsLock = 1;
    *tk_Alpha = 1;
  }
  if (scrollLock) {
    kbdLockingKeys.kbdLeds.bmScrollLock = 1;
  }
  hid->SetReport(0, 0, 2, 0, 1, &(kbdLockingKeys.bLeds));
}

void UsbKbdRptParser::updateModifier(uint8_t mask, uint8_t before, uint8_t after, byte* xtkey)
{
  boolean wasMod = before & mask;
  boolean isMod = after & mask;
  if (wasMod && (!isMod)) {
    // RELEASE MODIFIER
  } else if (isMod && (!wasMod)) {
    // PRESS MODIFIER
  }
}

void UsbKbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after)
{
  updateModifier(U_RIGHTSHIFT, before, after, XT_RSHIFT);
  updateModifier(U_LEFTSHIFT, before, after, XT_LSHIFT
  updateModifier(U_RIGHTALT, before, after, XT_RALT);
  updateModifier(U_LEFTALT, before, after, XT_LALT);
  updateModifier(U_RIGHTCTRL, before, after, XT_RCTRL);
  updateModifier(U_LEFTCTRL, before, after, XT_LCTRL);
}

void UsbKbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
}

void UsbKbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
}



#endif

