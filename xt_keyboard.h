#ifndef _XT_KEYBOARD_H
#define _XT_KEYBOARD_H

#include <QueueArray.h>

QueueArray<unsigned char> xt_keybuffer;
boolean selftest = true;

#define xt_clk 0
#define xt_data 1

void xt_write(unsigned char value);

void xt_setup() {
  pinMode(xt_clk, OUTPUT); 
  pinMode(xt_data, OUTPUT); 
  digitalWrite(xt_clk, HIGH); 
  digitalWrite(xt_data, LOW);
  pinMode(xt_clk, INPUT);
  pinMode(xt_data, INPUT); 
}

void xt_loop() {
  // Respond to power-on self test
  if (selftest && digitalRead(xt_clk) == LOW) {
    delay(10);
    xt_write(0xAA);
    selftest = false;
  } else {
    noInterrupts();
    while(!xt_keybuffer.isEmpty()) {
      unsigned char keycode = xt_keybuffer.dequeue();
      xt_write(keycode);      
    }
    interrupts();
  }
}

void xt_waitForCts() {
  while (digitalRead(xt_clk) == LOW || digitalRead(xt_data) == LOW) {
    delayMicroseconds(15);
  }
  delayMicroseconds(50);
}

void xt_sendBit(boolean bit) {
  digitalWrite(xt_data, bit ? HIGH : LOW);
  digitalWrite(xt_clk, HIGH);
  delayMicroseconds(55);
  digitalWrite(xt_clk, LOW);
  delayMicroseconds(30);
}

void xt_write(unsigned char value) { 
   
   unsigned char bits[8] ;
   byte p = 0 ; 
   byte j = 0 ;

   for (j=0 ; j < 8; j++) {
     if (value & 1) bits[j] = 1 ;
     else bits[j] = 0 ; 
     value = value >> 1 ; 
   }

   xt_waitForCts();

   pinMode(xt_clk, OUTPUT);
   pinMode(xt_data, OUTPUT);

   xt_sendBit(1);
      
   byte i = 0 ; 

   for (i=0; i < 8; i++) {
      xt_sendBit(bits[p]);
      p++ ; 
   } 

   digitalWrite(xt_clk, HIGH); 
   digitalWrite(xt_data, HIGH);  
   
   pinMode(xt_clk, INPUT);
   pinMode(xt_data, INPUT);
}

void xt_break(unsigned char value) {
  noInterrupts();
  xt_keybuffer.enqueue(0x80 | value);
  interrupts();
}

void xt_make(unsigned char value) {
  noInterrupts();
  xt_keybuffer.enqueue(value);
  interrupts();
}



#endif

