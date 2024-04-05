#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
#define INA1 26
#define INB1 27
#define INA2 28
#define INB2 29
#define INA3 2
#define INB3 A0
#define PWM1 10
#define PWM2 9
#define PWM3 3
void motor(byte vel, byte motor);
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(1, motor);
  pinMode(INA1, 1);
  pinMode(INB1, 1);
  pinMode(PWM1, 1);
  pinMode(INA2, 1);
  pinMode(INB2, 1);
  pinMode(PWM2, 1);
  pinMode(INA3, 1);
  pinMode(INB3, 1);
  pinMode(PWM3, 1);
}
void motor(byte vel, byte motor) {
  int in1 = 0, in2 = 0, pwmPin = 0;
  if (motor == 1) {
    in1 = INA1;
    in2 = INB1;
    pwmPin = PWM1;
  }
  if (motor == 2) {
    in1 = INA2;
    in2 = INB2;
    pwmPin = PWM2;
  }
  if (motor == 3) {
    in1 = INA3;
    in2 = INB3;
    pwmPin = PWM3;
  }

  ///

  int vel_1 = (int)vel;
  //vel_1 = map(vel_1, 0, 255, -255, 255);
  vel_1 = vel_1 * 2 - 255;
  digitalWrite(in1, !(vel_1 >= 0));
  digitalWrite(in2, (vel_1 > 0));

  /*Serial.print("\tm2: ");
  Serial.print(m2);
  Serial.print("\tm3: ");
  Serial.println(m3);
*/
  for (int i = 0; i < motor; i++) {
    Serial.print('\t');
  }
  Serial.print("m1: ");
  Serial.println(vel_1);
  vel_1 = abs(vel_1);


  analogWrite(pwmPin, vel_1);
}


void loop() {
  Enotik.work();
}
/*if (vel_2 < STICK_LUFT && vel_2 > -STICK_LUFT) {
    v1_1 = 0;
    v2_1 = 0;
  }
  if (v2_1 < STICK_LUFT && v2_1 > -STICK_LUFT) {
    v1_1 = 0;
    v2_1 = 0;
  }*/
