#ifndef _XT_KEYBOARD_H
#define _XT_KEYBOARD_H

#define xt_clk 2
#define xt_data 5

void xt_setup() {
  pinMode(xt_clk, OUTPUT) ; 
  pinMode(xt_data, OUTPUT) ; 
  digitalWrite(xt_clk, HIGH) ; 
  digitalWrite(xt_data, HIGH) ; 
}

void xt_loop() {
  // Respond to power-on self test
  if (digitalRead(xt_clk) == LOW) {
    delay(10);
    xt_write(0xAA);
  }
}

void xt_break(unsigned char value) {
  xt_write(0x80 ^ value);
}

void xt_write(unsigned char value) { 
   while (digitalRead(xt_clk) != HIGH) ; 

   unsigned char bits[8] ;
   byte p = 0 ; 
   byte j = 0 ;

   for (j=0 ; j < 8; j++) {
     if (value & 1) bits[j] = 1 ;
     else bits[j] = 0 ; 
     value = value >> 1 ; 
   }

   digitalWrite(xt_clk, LOW) ; 
   digitalWrite(xt_data, HIGH) ; 
   delayMicroseconds(120) ; 
   digitalWrite(xt_clk, HIGH) ; 
   delayMicroseconds(66) ;
   digitalWrite(xt_clk, LOW) ; 
   delayMicroseconds(30) ;
   digitalWrite(xt_clk, HIGH) ; 
   byte i = 0 ; 

   for (i=0; i < 8; i++) {
      digitalWrite(xt_clk, HIGH) ; 
      digitalWrite(xt_data, bits[p]) ; 
      delayMicroseconds(95) ;
      digitalWrite(xt_clk, LOW) ;
      digitalWrite(xt_data, LOW) ; 
      p++ ; 
   } 

   digitalWrite(xt_clk, HIGH) ; 
   digitalWrite(xt_data, LOW) ;  
   delay(1) ;
}

#endif

