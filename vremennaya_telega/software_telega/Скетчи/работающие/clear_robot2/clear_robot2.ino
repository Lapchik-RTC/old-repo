#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
//#include "ryabina.h"
#include <Servo.h>

//////////////

Servo ServoVN;
//Servo ServoZAHVAT;
Servo Servo180;
Servo ServoUp1;
Servo ServoUp2;
Servo ServoShvatUp;

//////////////

#define DELTA_SOFT_SPEED_PWM 15
#define DELTA_SOFT_TIME_MS 5
#define MAX_MOTOR_CURRENT_MA 1300
#define CURRENT_KP 0.1

void Manipulator2(byte, byte);

void Drive_Normal(byte, byte);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(2, Drive_Normal);
  Enotik.bind(5, Manipulator2);

  
  //ServoZAHVAT.attach(2);
  ServoShvatUp.attach(3);
  ServoVN.attach(5);
  motor1.init(DELTA_SOFT_SPEED_PWM , DELTA_SOFT_TIME_MS, MAX_MOTOR_CURRENT_MA, CURRENT_KP);
  motor2.init(DELTA_SOFT_SPEED_PWM , DELTA_SOFT_TIME_MS, MAX_MOTOR_CURRENT_MA, CURRENT_KP);
  //ServoZAHVAT.write(90);
  //delay(1000);
  //ServoZAHVAT.write(120);
  //delay(1000);
  //ServoZAHVAT.write(90);
  //delay(1000);
}

void loop() {
  Enotik.work();
  motor1.work();
  motor2.work();
}



void Manipulator2(byte man1, byte shvat1)
{
  Serial.println("servo");
  //Serial.println('Manipulator');
  //motor1.brake();
  //motor2.brake();
  int man = (int) man1;
  int shvat = (int) shvat1;

  if (shvat < -1000) {
    shvat = -1000;
  }

  if (shvat > 1000) {
    shvat = 1000;
  }
  if (man < -1000) {
    man = -1000;
  }
  if (man > 1000) {
     man = 1000;
  }
  Servo180.write(shvat);
  
  ServoVN.write(man);
};


void Drive_Normal(byte v1, byte v2)
{
  Serial.println('Drive_n');
  int v1_1 = (int) v1;
  int v2_1 = (int) v2;
  v1_1 = v1_1 * 2 - 255;
  v2_1 = v2_1 * 2 - 255;
  if (v1_1 < 10 && v1_1 > -10) {
    motor1.brake();
  }
  if (v2_1 < 10 && v2_1 > -10) {
    motor2.brake();
  }

  if (v1_1 > 240) {
    v1_1 = 240;
  }
  else {
    if (v1_1 < -240) {
      v1_1 = -240;
    };
  };
  if (v2_1 > 240) {
    v2_1 = 240;
  }
  else {
    if (v2_1 < -240) {
      v2_1 = -240;
    };
  };
  motor1.drive(v1_1);
  motor2.drive(v2_1);
}
