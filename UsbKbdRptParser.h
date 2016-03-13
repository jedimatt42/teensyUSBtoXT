#ifndef _USB_KBD_RPT_PARSER_H
#define _USB_KBD_RPT_PARSER_H

#include <hidboot.h>

#include "USBCodes.h"
#include "XTCodes.h"
#include "xt_keyboard.h"

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
    void updateModifier(uint8_t mask, uint8_t before, uint8_t after, uint16_t xtkey);
    void setXtKeyState(uint16_t xtkey, boolean state);
    void handleKey(uint8_t usbkey, boolean state);

  public:
    UsbKbdRptParser();
    void setKeyLocks(HID* hid, boolean numLock, boolean capsLock, boolean scrollLock);
};

UsbKbdRptParser::UsbKbdRptParser() {
}

void UsbKbdRptParser::setKeyLocks(HID* hid, boolean numLock, boolean capsLock, boolean scrollLock) { 
  if (numLock) {
    kbdLockingKeys.kbdLeds.bmNumLock = 1;
  }
  if (capsLock) {
    kbdLockingKeys.kbdLeds.bmCapsLock = 1;
  }
  if (scrollLock) {
    kbdLockingKeys.kbdLeds.bmScrollLock = 1;
  }
  hid->SetReport(0, 0, 2, 0, 1, &(kbdLockingKeys.bLeds));
}

void UsbKbdRptParser::updateModifier(uint8_t mask, uint8_t before, uint8_t after, uint16_t xtkey) {
  boolean wasMod = before & mask;
  boolean isMod = after & mask;
  if (wasMod && (!isMod)) {
    // RELEASE MODIFIER
    setXtKeyState(xtkey, false);
  } else if (isMod && (!wasMod)) {
    // PRESS MODIFIER
    setXtKeyState(xtkey, true);
  }
}

void UsbKbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {
  updateModifier(U_RIGHTSHIFT, before, after, XT_RSHIFT);
  updateModifier(U_LEFTSHIFT, before, after, XT_LSHIFT);
  updateModifier(U_RIGHTALT, before, after, XT_RALT);
  updateModifier(U_LEFTALT, before, after, XT_LALT);
  updateModifier(U_RIGHTCTRL, before, after, XT_RCTRL);
  updateModifier(U_LEFTCTRL, before, after, XT_LCTRL);
}

void UsbKbdRptParser::OnKeyDown(uint8_t mod, uint8_t key) {
  handleKey(key, true);
}

void UsbKbdRptParser::OnKeyUp(uint8_t mod, uint8_t key) {
  handleKey(key, false);
}

void UsbKbdRptParser::setXtKeyState(uint16_t xtkey, boolean make) {
  uint8_t prefix = (uint8_t) (0xFF & (xtkey >> 8));
  if (prefix) {
    xt_make(prefix);
  }

  if (make) {
    xt_make((uint8_t)(xtkey & 0xFF));
  } else {
    xt_break((uint8_t)(xtkey & 0xFF));
  }
}

#define NUMLOCK(X,Y) (kbdLockingKeys.kbdLeds.bmNumLock?X:Y)  

void UsbKbdRptParser::handleKey(uint8_t usbkey, boolean state) {
  switch(usbkey) {
    case U_BACKQUOTE: 
      setXtKeyState(XT_BACKQUOTE, state); break;
    case U_OPENSQUARE: 
      setXtKeyState(XT_OPENSQUARE, state); break;
    case U_CLOSESQUARE:
      setXtKeyState(XT_CLOSESQUARE, state); break;
    case U_BACKSLASH:
      setXtKeyState(XT_BACKSLASH, state); break;
    case U_SLASH:
      setXtKeyState(XT_SLASH, state); break;
    case U_HYPHEN:
      setXtKeyState(XT_HYPHEN, state); break;
    case U_QUOTE:
      setXtKeyState(XT_QUOTE, state); break;
    case U_EQUAL:
      setXtKeyState(XT_EQUAL, state); break;
    case U_SEMICOLON:
      setXtKeyState(XT_SEMICOLON, state); break;
    case U_ENTER:
      setXtKeyState(XT_ENTER, state); break;
    case U_COMMA:
      setXtKeyState(XT_COMMA, state); break;
    case U_PERIOD:
      setXtKeyState(XT_PERIOD, state); break;
    case U_SPACE: 
      setXtKeyState(XT_SPACE, state); break;
    case U_BACKSPACE:
      setXtKeyState(XT_BACKSPACE, state); break;
    case U_LEFTARROW:
      setXtKeyState(XT_LEFT, state); break;
    case U_RIGHTARROW:
      setXtKeyState(XT_RIGHT, state); break;
    case U_UPARROW: 
      setXtKeyState(XT_UP, state); break;
    case U_DOWNARROW: 
      setXtKeyState(XT_DOWN, state); break;
    case U_HOME:
      setXtKeyState(XT_HOME, state); break;
    case U_END:
      setXtKeyState(XT_END, state); break;
    case U_F1:
      setXtKeyState(XT_F1, state); break;
    case U_F2:
      setXtKeyState(XT_F2, state); break;
    case U_F3:
      setXtKeyState(XT_F3, state); break;
    case U_F4:
      setXtKeyState(XT_F4, state); break;
    case U_F5:
      setXtKeyState(XT_F5, state); break;
    case U_F6:
      setXtKeyState(XT_F6, state); break;
    case U_F7:
      setXtKeyState(XT_F7, state); break;
    case U_F8:
      setXtKeyState(XT_F8, state); break;
    case U_F9:
      setXtKeyState(XT_F9, state); break;
    case U_F10:
      setXtKeyState(XT_F10, state); break;
    case U_F11:
      setXtKeyState(XT_F11, state); break;
    case U_F12:
      setXtKeyState(XT_F12, state); break;
    case U_DELETE:
      setXtKeyState(XT_DEL, state); break;
    case U_INSERT:
      setXtKeyState(XT_INSERT, state); break;
    case U_BREAK:
      setXtKeyState(XT_PAUSE, state); break;
    case U_PGDN:
      setXtKeyState(XT_PGDN, state); break;
    case U_PGUP: 
      setXtKeyState(XT_PGUP, state); break;
    case U_TAB: 
      setXtKeyState(XT_TAB, state); break;
    case U_ESC:
      setXtKeyState(XT_ESC, state); break;
    case U_CAPSLOCK:
      setXtKeyState(XT_CAPS_LOCK, state); break;
    case U_NUM1: 
      setXtKeyState(XT_NUM1, state); break;
    case U_NUM2:
      setXtKeyState(XT_NUM2, state); break;
    case U_NUM3:
      setXtKeyState(XT_NUM3, state); break;
    case U_NUM4:
      setXtKeyState(XT_NUM4, state); break;
    case U_NUM5:
      setXtKeyState(XT_NUM5, state); break;
    case U_NUM6:
      setXtKeyState(XT_NUM6, state); break;
    case U_NUM7:
      setXtKeyState(XT_NUM7, state); break;
    case U_NUM8:
      setXtKeyState(XT_NUM8, state); break;
    case U_NUM9:
      setXtKeyState(XT_NUM9, state); break;
    case U_NUM0: 
      setXtKeyState(XT_NUM0, state); break;
    case U_NUMPAD_1:
      setXtKeyState(NUMLOCK(XT_NUM1,XT_NUMPAD_1), state); break;
    case U_NUMPAD_2:
      setXtKeyState(NUMLOCK(XT_NUM2,XT_NUMPAD_2), state); break;
    case U_NUMPAD_3:
      setXtKeyState(NUMLOCK(XT_NUM3,XT_NUMPAD_3), state); break;
    case U_NUMPAD_4:
      setXtKeyState(NUMLOCK(XT_NUM4,XT_NUMPAD_4), state); break;
    case U_NUMPAD_5:
      setXtKeyState(NUMLOCK(XT_NUM5,XT_NUMPAD_5), state); break;
    case U_NUMPAD_6:
      setXtKeyState(NUMLOCK(XT_NUM6,XT_NUMPAD_6), state); break;
    case U_NUMPAD_7:
      setXtKeyState(NUMLOCK(XT_NUM7,XT_NUMPAD_7), state); break;
    case U_NUMPAD_8:
      setXtKeyState(NUMLOCK(XT_NUM8,XT_NUMPAD_8), state); break;
    case U_NUMPAD_9:
      setXtKeyState(NUMLOCK(XT_NUM9,XT_NUMPAD_9), state); break;
    case U_NUMPAD_0:
      setXtKeyState(NUMLOCK(XT_NUM0,XT_NUMPAD_0), state); break;
    case U_NUMPAD_PERIOD:
      setXtKeyState(NUMLOCK(XT_PERIOD,XT_NUMPAD_PERIOD), state); break;
    case U_NUMSLASH:
      setXtKeyState(XT_NUMPAD_SLASH, state); break;
    case U_NUMPAD_STAR:
      setXtKeyState(XT_NUMPAD_ASTERISK, state); break;
    case U_NUMPAD_HYPHEN:
      setXtKeyState(XT_NUMPAD_HYPHEN, state); break;
    case U_NUMPAD_PLUS:
      setXtKeyState(XT_NUMPAD_PLUS, state); break;
    case U_NUMPAD_ENTER:
      setXtKeyState(XT_NUMPAD_ENTER, state); break;
    case U_Q:
      setXtKeyState(XT_Q, state); break;
    case U_W:
      setXtKeyState(XT_W, state); break;
    case U_E: 
      setXtKeyState(XT_E, state); break;
    case U_R: 
      setXtKeyState(XT_R, state); break;
    case U_T: 
      setXtKeyState(XT_T, state); break;
    case U_Y: 
      setXtKeyState(XT_Y, state); break;
    case U_U: 
      setXtKeyState(XT_U, state); break;
    case U_I: 
      setXtKeyState(XT_I, state); break;
    case U_O: 
      setXtKeyState(XT_O, state); break;
    case U_P: 
      setXtKeyState(XT_P, state); break;
    case U_A: 
      setXtKeyState(XT_A, state); break;
    case U_S:
      setXtKeyState(XT_S, state); break;
    case U_D: 
      setXtKeyState(XT_D, state); break;
    case U_F: 
      setXtKeyState(XT_F, state); break;
    case U_G: 
      setXtKeyState(XT_G, state); break;
    case U_H:
      setXtKeyState(XT_H, state); break;
    case U_J:
      setXtKeyState(XT_J, state); break;
    case U_K:
      setXtKeyState(XT_K, state); break;
    case U_L:
      setXtKeyState(XT_L, state); break;
    case U_Z: 
      setXtKeyState(XT_Z, state); break;
    case U_X:
      setXtKeyState(XT_X, state); break;
    case U_C:
      setXtKeyState(XT_C, state); break;
    case U_V: 
      setXtKeyState(XT_V, state); break;
    case U_B:
      setXtKeyState(XT_B, state); break;
    case U_N:
      setXtKeyState(XT_N, state); break;
    case U_M:
      setXtKeyState(XT_M, state); break;
  }
}



#endif

