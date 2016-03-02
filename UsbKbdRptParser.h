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
  updateModifier(U_RIGHTSHIFT, before, after, xt_RShift);
  updateModifier(U_LEFTSHIFT, before, after, xt_LShift);
  updateModifier(U_LEFTALT | U_RIGHTALT, before, after, xt_Fctn);
  updateModifier(U_LEFTCTRL | U_RIGHTCTRL, before, after, xt_Ctrl);
}

#define ISSHIFT(X) ((U_LEFTSHIFT | U_RIGHTSHIFT) & X)
#define ISALT(X) ((U_LEFTALT | U_RIGHTALT) & X)
#define ISCTRL(X) ((U_LEFTCTRL | U_RIGHTCTRL) & X)

void UsbKbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
}

void UsbKbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
}



#endif

