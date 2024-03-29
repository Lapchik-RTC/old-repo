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
int eOld;
int p;
int d;
//////////////

#define DELTA_SOFT_SPEED_PWM 15
#define DELTA_SOFT_TIME_MS 5
#define MAX_MOTOR_CURRENT_MA 1300
#define CURRENT_KP 0.1
#define V 80
#define S 100
#define MS1 5
#define MS2 6
#define SHARP A14
#define Kp 1,1
#define Ki 0
#define Kd 8
#define MS3 7
#define Rellay 8
#define SHARPPIN A13
#define LED 45

void Manipulator2(byte, byte);

void Drive_Normal(byte, byte);








//////////////

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(2, Drive_Normal);
  Enotik.bind(5, Manipulator2);

  pinMode(SHARPPIN, INPUT);
  
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

/////////////auto

int Regulator1 (int Ustavka, int Znachenie)
{
  //Serial.println(Znachenie);
  int u;
  int er;
  unsigned long now = millis();
  unsigned long lastTime;
  double DeltaTime = (double) ( now - lastTime );
  er = Ustavka - Znachenie;
  p = er * Kp;
  d = Kd * ((er - eOld) / DeltaTime);
  u = p;
  eOld = er;
  lastTime = now;
  return u;
}

void Stena (byte nichego, byte K)
{
  Serial.println('Stena');
  int _K = (int) K;
  int perevod;
  if (_K == 1)
  {
    //ServoSHARP.write(150);
    motor1.drive(V - (Regulator1(S, analogRead(SHARP))));
    motor2.drive(V + (Regulator1(S, analogRead(SHARP))));
    //Serial.println(_K);
  }else{

  
    //ServoSHARP.write(10);
  }
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
