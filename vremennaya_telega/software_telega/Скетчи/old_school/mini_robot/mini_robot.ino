#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
//#include "motor.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"

#define EN1 5
#define IN1 4
#define IN2 11
#define EN2 6
#define IN3 7
#define IN4 12

#define EN1_2 9
#define IN1_2 8
#define IN2_2 13

//////////

void Drive_Normal(byte, byte);
void drive(int, int);
void drive2(byte, byte);

//////////
void setup() {
  Serial1.begin(9600);
  Enotik.init_slave(0x01);
  pinMode (EN1, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (EN2, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (EN1_2, OUTPUT);
  pinMode (IN1_2, OUTPUT);
  pinMode (IN2_2, OUTPUT);
  Enotik.bind(4, Drive_Normal);
  
}

void loop() {
  Enotik.work();
  //motor1.work();
  //motor2.work();

}


void Drive_Normal(byte v1, byte v2)
{
  //Serial1.println(v1);
  int v1_1 = (int) v1;
  int v2_1 = (int) v2;
  v1_1 = v1_1 * 2 - 255;
  v2_1 = v2_1 * 2 - 255;
  if (v1_1 < 10 && v1_1 > -10) {
    drive(0, 0);
  }
  if (v2_1 < 10 && v2_1 > -10) {
    drive(0, 0);
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
  drive(v1_1, v2_1);
}


void drive(int left, int right)
{
  //left = constrain(left, -255, 255);
 // right = constrain(right, -255, 255);

  if (left >= 0){
    digitalWrite(IN3, HIGH);
  //  Serial1.println("f");
  analogWrite(IN4, 0);
  }
  else{
    digitalWrite(IN3, LOW);
 analogWrite(IN4, 255);
 //Serial1.println("fJ");
  }
  if (right >= 0){
    digitalWrite(IN1, HIGH);
 analogWrite(IN2, 0);
 //Serial.println("fP");
  }
  else{
    digitalWrite(IN1, LOW);
 analogWrite(IN2, 255);
 //Serial.println("fG");
  }
  analogWrite(EN2, abs(left));
  analogWrite(EN1, abs(right));

}

void drive2(byte right, byte nicego)
{
  int t = (int) right;
 
  t = constrain(right, -255, 255);

  if (t >= 0){
    digitalWrite(IN1_2, HIGH);
  digitalWrite(IN2_2, LOW);
  }
  else{
    digitalWrite(IN1_2, LOW);
  digitalWrite(IN2_2, HIGH);
  }

   analogWrite(EN1_2, abs(t));

}
