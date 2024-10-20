//==========================================================================
// Gimbal Clock - servos.h
//
// Copyright (c) 2024, Moritz v. Sivers
//
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef SERVOS_H
#define SERVOS_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  130 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

const uint16_t DELAY = 15;   // delay (ms) between servo position update

// servo positions for each digit
const int MINPOS[10][4] = { {280,420,190,490}, {460,420,190,300}, {370,130,190,300}, {370,320,190,300}, {280,420,190,300}, {370,500,190,300}, {370,420,100,300}, {370,420,290,490}, {370,420,290,300}, {370,500,190,490} }; // motors 6, 7, 8, 15
const int TOMPOS[6][3] = { {300,170,480}, {490,170,290}, {400,70,290}, {400,260,290}, {300,170,290}, {400,440,290}  }; // motors 4, 5, 14
const int HOURPOS[10][4] =  { {290,330,260,250}, {480,330,260,50}, {390,10,260,50}, {390,230,260,50}, {290,330,260,50}, {390,420,260,50}, {390,330,150,50}, {390,330,340,250}, {390,330,340,50}, {390,420,260,250} };  // motors 1, 2, 3, 13
const int TOHPOS[3][2] = { {270,50}, {270,230}, {90,50} }; // motors 0, 12  

// put servos to sleep
//
void sleepServos() {

  Serial.println("put servos to sleep");
  for (uint8_t servonum = 0; servonum<16; servonum++) {
    pwm.setPWM(servonum,0,0);  
  }

}

void moveServoMax(uint8_t servonum) {
  for(uint16_t pos=SERVOMIN+1; pos<=SERVOMAX; pos++) {
    pwm.setPWM(servonum, 0, pos);
    delay(DELAY);
  }
  pwm.setPWM(servonum,0,0);
}

void moveServoMin(uint8_t servonum) {
  for(uint16_t pos=SERVOMAX-1; pos>=SERVOMIN; pos--) {
    pwm.setPWM(servonum, 0, pos);
    delay(DELAY);
  }
  pwm.setPWM(servonum,0,0);
}

void moveAllMax() {
  for (uint8_t servonum = 0; servonum<16; servonum++) {
    pwm.setPWM(servonum, 0, SERVOMAX);
    pwm.setPWM(servonum,0,0);
    delay(1000);
  }
}

void moveAllMin() {
  for (uint8_t servonum = 0; servonum<16; servonum++) {
    pwm.setPWM(servonum, 0, SERVOMIN);
    pwm.setPWM(servonum,0,0);
    delay(1000);
  }
}

void testServos() {

  for (uint8_t servonum = 0; servonum<16; servonum++) {
    moveServoMin(servonum);
    delay(500);
    moveServoMax(servonum);
    delay(500);
  }
}

void showDigit(uint8_t dignum, uint8_t digit) {
  switch (dignum) {
      case 0 :  // minutes
          pwm.setPWM(6, 0, MINPOS[digit][0]);
          delay(500);   // wait until servo has moved
          pwm.setPWM(7, 0, MINPOS[digit][1]);
          delay(500);   // wait until servo has moved
          pwm.setPWM(8, 0, MINPOS[digit][2]);
          delay(500);   // wait until servo has moved
          pwm.setPWM(15, 0, MINPOS[digit][3]);
          delay(500);   // wait until servo has moved
          break;
      case 1 : // tom
          pwm.setPWM(4, 0, TOMPOS[digit][0]);
          delay(500);   // wait until servo has moved 
          pwm.setPWM(5, 0, TOMPOS[digit][1]);
          delay(500);   // wait until servo has moved 
          pwm.setPWM(14, 0, TOMPOS[digit][2]); 
          delay(500);   // wait until servo has moved
          break;
      case 2 : // hours
          pwm.setPWM(1, 0, HOURPOS[digit][0]);
          delay(500);   // wait until servo has moved 
          pwm.setPWM(2, 0, HOURPOS[digit][1]);
          delay(500);   // wait until servo has moved
          pwm.setPWM(3, 0, HOURPOS[digit][2]);
          delay(500);   // wait until servo has moved
          pwm.setPWM(13, 0, HOURPOS[digit][3]);
          delay(500);   // wait until servo has moved
          break;
      case 3 : // toh
          pwm.setPWM(0, 0, TOHPOS[digit][0]); 
          delay(500);   // wait until servo has moved
          pwm.setPWM(12, 0, TOHPOS[digit][1]);
          delay(500);   // wait until servo has moved
          break;
    }
    sleepServos();
}




#endif //SERVOS_H
