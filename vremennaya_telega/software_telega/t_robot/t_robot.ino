#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
//#include "ryabina.h"
#include <Servo.h>

#define INA1 26
#define INB1 27
#define INA2 28
#define INB2 29
#define PWM1 9
#define PWM2 10

#define KLINE 0.8 
void motor(int v1,int v2);
int line();
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(2, motor);
  //Enotik.bind(5, Manipulator2);

  //serv.attach(SERVO1_PIN);
  pinMode(INA1, 1);
  pinMode(INB1, 1);
  pinMode(PWM1, 1);
  pinMode(INA2, 1);
  pinMode(INB2, 1);
  pinMode(PWM2, 1);
}
void motor(int v1, int v2){
  digitalWrite(INA1, !(v1>=0));
  digitalWrite(INB1, (v1>0));
  digitalWrite(INA2, !(v2>=0));
  digitalWrite(INB2, (v2>=0));
  v1=abs(v1);
  v2=abs(v2);
  if(v1>250)
    v1=250;
  if(v2>250)
    v2=250;
  int v1_1 = (int) v1;
  int v2_1 = (int) v2;
  v1_1 = v1_1 * 2 - 255;
  v2_1 = v2_1 * 2 - 255;
  if (v1_1 < 10 && v1_1 > -10) {
    analogWrite(PWM1, 0);
  }
  if (v2_1 < 10 && v2_1 > -10) {
     analogWrite(PWM2, 0);
  }
  analogWrite(PWM1, v1_1);
  analogWrite(PWM2, v2_1);
}
void loop() {
  Enotik.work();
}
/*

int line(){
  static int err=0, errOld=0;
  errOld=err;
  err=analogRead(A0)-analogRead(A1);
  int uvel = err*KLINE;
  return uvel;
}
*/