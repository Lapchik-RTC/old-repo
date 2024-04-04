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
#define KLINE 0.3
#define LINE_VEL 20
#define STICK_LUFT 20
#define MAX_SPEED 90
Servo upserv;
Servo cserv;
void motor(byte v1, byte v2);
void line();
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(2, motor);
  Enotik.bind(5, zahvat);
  Enotik.bind(3, line);
  upserv.attach(3);
  cserv.attach(2);
  cserv.write(40);
  //serv.attach(SERVO1_PIN);
  pinMode(INA1, 1);
  pinMode(INB1, 1);
  pinMode(PWM1, 1);
  pinMode(INA2, 1);
  pinMode(INB2, 1);
  pinMode(PWM2, 1);
}


void zahvat(byte buttOn1, byte buttOn2) {
  if (buttOn1) {
    upserv.write(120);
  } else {
    upserv.write(0);
  }
  if (buttOn2) {
    cserv.write(12);
  } else {
    cserv.write(50);
  }
}



void line(byte lineOn, byte a) {
  if (lineOn) {
    static int err = 0, errOld = 0, velr=0, vell;
    //errOld = err;
    err = analogRead(A1) - analogRead(A0);
    float uvel = err * KLINE;
    velr = LINE_VEL-uvel;
    vell = LINE_VEL+uvel;
    if(analogRead(A1)>620 && analogRead(A0)>630){
      velr = LINE_VEL;
      vell = LINE_VEL;
    } 
    digitalWrite(INA1, !(velr >= 0));
    digitalWrite(INB1, (velr > 0));
    digitalWrite(INA2, !(vell >= 0));
    digitalWrite(INB2, (vell >= 0));

    velr = abs(velr);
    vell = abs(vell);

    analogWrite(PWM1, velr);
    analogWrite(PWM2, vell);

    Serial.print("uvel:");
    Serial.print(uvel);
    Serial.print("\t1:");
    Serial.print(analogRead(A1));
    Serial.print("\t0:");
    Serial.println(analogRead(A0));
  }
}



void motor(byte v1, byte v2) {

  // if (v1 > 250)
  //   v1 = 250;
  // if (v2 > 250)
  //   v2 = 250;
  int v1_1 = (int)v1;
  int v2_1 = (int)v2;
  v1_1 = v1_1 * 2 - 255;
  v2_1 = v2_1 * 2 - 255;
  digitalWrite(INA1, !(v1_1 >= 0));
  digitalWrite(INB1, (v1_1 > 0));
  digitalWrite(INA2, !(v2_1 >= 0));
  digitalWrite(INB2, (v2_1 >= 0));
  if (v1_1 < STICK_LUFT && v1_1 > -STICK_LUFT) {
    v1_1 = 0;
    v2_1 = 0;
  }
  if (v2_1 < STICK_LUFT && v2_1 > -STICK_LUFT) {
    v1_1 = 0;
    v2_1 = 0;
  }
  v1_1 = abs(v1_1);
  v2_1 = abs(v2_1);

  analogWrite(PWM1, v1_1);
  analogWrite(PWM2, v2_1);
}
void loop() {
  Enotik.work();
}
/*


}
*/