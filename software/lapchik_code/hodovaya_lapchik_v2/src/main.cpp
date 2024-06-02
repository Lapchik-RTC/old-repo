#include <Arduino.h>
#include"def.h"
#include"crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
//#include "motor.h"
#include "parser.h"
#include "Periph.h"
#include "hodovaya.h"

const uint8_t reverses[] = { 0, 0, 1, 0, 1, 0 };

void encoder0();
void encoder1();
void encoder2();
void encoder3();
void encoder4();
void encoder5();

void foo(int speed1, int speed2);
// void write0(int);
// void write1(int);
// void write2(int);
// void write3(int);
// void write4(int);
// void write5(int);


void group1(int val);
void group2(int val);
// int32_t gEncoder0 = 0;
// int32_t gEncoder1 = 0;
// int32_t gEncoder2 = 0;
// int32_t gEncoder3 = 0;
// int32_t gEncoder4 = 0;
// int32_t gEncoder5 = 0;





mymotor motor0;
mymotor motor1;
mymotor motor2;
mymotor motor3;
mymotor motor4;
mymotor motor5;
mytelega telega;
void setup() {
    Serial.begin(9600);
    Serial3.begin(250000);
    motor0.attach(INA0, INB0, PWM0, CS0, INTERRUPT_PIN0, DIRECTION_PIN0, 0.2);
    motor1.attach(INA1, INB1, PWM1, CS1, INTERRUPT_PIN1, DIRECTION_PIN1, 0.2);
    motor2.attach(INA2, INB2, PWM2, CS2, INTERRUPT_PIN2, DIRECTION_PIN2, 0.2);
    motor3.attach(INA3, INB3, PWM3, CS3, INTERRUPT_PIN3, DIRECTION_PIN3, 0.2);
    motor4.attach(INA4, INB4, PWM4, CS4, INTERRUPT_PIN4, DIRECTION_PIN4, 0.2);
    motor5.attach(INA5, INB5, PWM5, CS5, INTERRUPT_PIN5, DIRECTION_PIN5, 0.2);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN0), encoder0, RISING);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN1), encoder1, RISING);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN2), encoder2, RISING);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN3), encoder3, RISING);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN4), encoder4, RISING);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN5), encoder5, RISING);
    
    telega.set(motor0, motor1, motor2, motor3, motor4, motor5);
}




void loop() 
{
  // group1(450);  
  foo(450, 450);
  //group2(450);
  telega.csSens();
}



void group1(int val)
{

}

void group2(int val)
{
    
}

//////////////////////////////////////////////___ENCODERS___//////////////////////////////////////////////
void encoder0()
{
  if(digitalRead(DIRECTION_PIN0))
    motor0.setEnc(reverses[0] * 2 - 1);
  else
    motor0.setEnc(-(reverses[0] * 2 - 1));
  motor0.setEnc(motor0.getEnc()/0.18);
}

void encoder1()
{
  if(digitalRead(DIRECTION_PIN1))
    motor1.setEnc(reverses[1] * 2 - 1);
  else
    motor1.setEnc(-(reverses[1] * 2 - 1));
}

void encoder2(){
  if(digitalRead(DIRECTION_PIN2))
    motor2.setEnc(reverses[2] * 2 - 1);
  else
    motor2.setEnc(-(reverses[2] * 2 - 1));
}

void encoder3(){
  if(digitalRead(DIRECTION_PIN3))
    motor3.setEnc(reverses[3] * 2 - 1);
  else
    motor3.setEnc(-(reverses[3] * 2 - 1));

}

void encoder4(){
  if(digitalRead(DIRECTION_PIN4))
    motor4.setEnc(reverses[4] * 2 - 1);
  else
    motor4.setEnc(-(reverses[4] * 2 - 1));
}

void encoder5(){
  if(digitalRead(DIRECTION_PIN5))
    motor5.setEnc(reverses[5] * 2 - 1);
  else
    motor5.setEnc(-(reverses[5] * 2 - 1));
}//*/


////////////////////////////////////////////////////////////////////////////////////////////////

void foo(int speed, int speed2){
  static uint32_t oldTime = millis();

  float kp = 0.4;

  static float desireableEcn = 0, desireableEcn2 = 0;
  int deltaT = millis() - oldTime;
  desireableEcn += (speed * deltaT / 1000);
  //desireableEcn2 += (speed2 * deltaT / 1000);
  
  int err0 = desireableEcn - (motor0.getEnc()/*0.18*/) + 450;
  int err1 = desireableEcn - (motor1.getEnc());
  int err2 = desireableEcn - (motor2.getEnc()) + 450;
  int err3 = desireableEcn - (motor3.getEnc());
  int err4 = desireableEcn - (motor4.getEnc()) + 450;
  int err5 = desireableEcn - (motor5.getEnc());

  motor0.power(err0 * kp);
  motor1.power(err1 * kp);
  motor2.power(err2 * kp);
  motor3.power(err3 * kp);
  motor4.power(err4 * kp);
  motor5.power(err5 * kp);

  oldTime = millis();
  delay(10);
}





//motor0
// void write0(int speed)
// {
//   static uint32_t oldTime = millis();

//   static float desireableEcn = 225;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);
  
//   int err = desireableEcn - (motor0.getEnc()/0.18);
  
//   motor0.power(err * motor0.getK());
//   oldTime = millis();
//   delay(10);
// }

// //motor1
// void write1(int speed)
// {
//   static uint32_t oldTime = millis();

//   static float desireableEcn = 0;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);
  
//   int err = desireableEcn - motor1.getEnc();
  
//   motor1.power(err * motor1.getK());
//   oldTime = millis();
//   delay(10);
// }

// //motor2
// void write2(int speed)
// {
//   static uint32_t oldTime = millis();

//   static float desireableEcn = 225;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);
  
//   int err = desireableEcn - motor2.getEnc();
  
//   motor2.power(err * motor2.getK());
//   oldTime = millis();
//   delay(10);
// }

// //motor3
// void write3(int speed)
// {
//   static uint32_t oldTime = millis();

//   static float desireableEcn = 0;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);
  
//   int err = desireableEcn - motor3.getEnc();
  
//   motor3.power(err * motor3.getK());
//   oldTime = millis();
//   delay(10);
// }

// //motor4
// void write4(int speed)
// {
//   static uint32_t oldTime = millis();

//   static float desireableEcn = 225;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);
  
//   int err = desireableEcn - motor4.getEnc();
  
//   motor4.power(err * motor4.getK());
//   oldTime = millis();
//   delay(10);
// }

// //motor5
// void write5(int speed)
// {
//   static uint32_t oldTime = millis();

//   static float desireableEcn = 0;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);
  
//   int err = desireableEcn - motor5.getEnc();
  
//   motor5.power(err * motor5.getK());
//   oldTime = millis();
//   delay(10);
// }