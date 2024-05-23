#include <Arduino.h>
#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
#include <mymotor.h>
#include "MotorLib.h"


//motor1
#define ENC1 18
#define INA1 32
#define INB1 34
#define PWM1 4
#define CS1 A4
//motor2
#define ENC2 21
#define INA2 33
#define INB2 35
#define PWM2 6
#define CS2 A2
//motor3
#define ENC3 19
#define INA3 36
#define INB3 38
#define PWM3 8
#define CS3 A0
//motor4
#define ENC4 18
#define INA4 37
#define INB4 39
#define PWM4 10
#define CS4 A1
//motor5
#define ENC5 3
#define INA5 40
#define INB5 42
#define PWM5 12
#define CS5 A3
//motor6
#define ENC6 2
#define INA6 41
#define INB6 43
#define PWM6 13
#define CS6 A5

/*#define kMotor 2
#define kiMotor 0.01
//uint8_t motorPins[] = { 8, 9, 5, 4, 10, 11, 7, 6 };
uint8_t motorPins[] = { INA1, INB1, INA2, INB2, INA3, INB3, INA4, INB4, INA5, INB5, INA6, INB6 };
MOTORS motor[6];
int32_t *motorEncs[6];
const uint8_t interrupts[] = { ENC1, ENC2, ENC3, ENC4, ENC5, ENC6 };
const uint8_t reverses[] = { 1, 0, 1, 0, 1, 0 };
const uint8_t directionPins[] = { CS1, CS2, CS3, CS4, CS5, CS6 };

void interr0() {
  *motorEncs[0] = *motorEncs[0] - (reverses[0] * 2 - 1) * (digitalRead(directionPins[0]) * 2 - 1);
}

void interr1() {
  *motorEncs[1] = *motorEncs[1] - (reverses[1] * 2 - 1) * (digitalRead(directionPins[1]) * 2 - 1);
}

void interr2() {
  *motorEncs[2] = *motorEncs[2] - (reverses[2] * 2 - 1) * (digitalRead(directionPins[2]) * 2 - 1);
}

void interr3() {
  *motorEncs[3] = *motorEncs[3] - (reverses[3] * 2 - 1) * (digitalRead(directionPins[3]) * 2 - 1);
}*/

class Mymotor{
    public:
    void attach(uint8_t ma, uint8_t mb, uint8_t mpwm){
      _maPin = ma;
      _ma = digitalPinToPort(ma);
      _mb = digitalPinToPort(mb);
    }
    void cout(){
      Serial.println("pin");
    }
    
    private:
    uint8_t _ma, _mb, _mpwm, _maPin;
};
Mymotor motorLF;

//=================SETUP=================
void setup() {
  Serial.begin(9600);
  Serial3.begin(250000);
  pinMode(INA1, 1);
  pinMode(INB1, 1);
  pinMode(PWM1, 1);
  pinMode(INA2, 1);
  pinMode(INB2, 1);
  pinMode(PWM2, 1);
  pinMode(INA3, 1);
  pinMode(INB3, 1);
  pinMode(PWM3, 1); 
  pinMode(INA4, 1);
  pinMode(INB4, 1);
  pinMode(PWM4, 1);
  pinMode(INA5, 1);
  pinMode(INB5, 1);
  pinMode(PWM5, 1);
  pinMode(INA6, 1);
  pinMode(INB6, 1);
  pinMode(PWM6, 1);
  motorLF.attach(INA1, INB1, PWM1);
}

void loop() {
  Enotik.work();
}