#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"
#include <Servo.h>
#define axis_X A4
#define axis_Y A5
#define zbutt1 A2
#define zbutt2 50
#define MAX_SPEED 90
#define FILTR_K 20

Servo upserv;
Servo cserv;
void zahvat();
void line();
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  upserv.attach(3);
  cserv.attach(2);
  Enotik.init_master(0x01);
  pinMode(axis_X, INPUT);
  pinMode(axis_Y, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(8, INPUT);
  pinMode(5, INPUT);
  pinMode(zbutt1, INPUT);
  pinMode(zbutt2, INPUT);
}
bool zb1 = 0, zb2 = 0, buttOn1 = 0, buttOn2 = 0;

void zahvat() {
  if ((analogRead(zbutt1) > 800) && buttOn1 == 0) {
    while ((analogRead(zbutt1)>800)) {}
    buttOn1 = 1;
  }
  if ((analogRead(zbutt1) > 800) && buttOn1 == 1) {
    while ((analogRead(zbutt1)>800)) {}
    buttOn1 = 0;
  }
  if (digitalRead(zbutt2) == 1 && buttOn2 == 0) {
    while (digitalRead(zbutt2) == 1) {}
    buttOn2 = 1;
  }
  if (digitalRead(zbutt2) == 1 && buttOn2 == 1) {
    while (digitalRead(zbutt2) == 1) {}
    buttOn2 = 0;
  }
  // Serial.print(buttOn1);
  // Serial.print(" ");
  // Serial.println(buttOn2);
  Enotik.send_message(5, buttOn1, buttOn2);
}
bool buttOn3=0;
void line(){
  if (digitalRead(3) == 1 && buttOn3 == 0) {
    while (digitalRead(3) == 1) {}
    buttOn3 = 1;
  }
  if (digitalRead(3) == 1 && buttOn3 == 1) {
    while (digitalRead(3) == 1) {}
    buttOn3 = 0;
  }
  Enotik.send_message(3, buttOn3, 1);
}


void sendmotors(int X1, int Y1) {
  int m1 = 0;
  int m2 = 0;
  int speed1 = 0;
  int speed2 = 0;
  m1 = Y1 + X1;
  m2 = Y1 - X1;

  if (m1 > MAX_SPEED)
    m1 = MAX_SPEED;
  if (m2 > MAX_SPEED)
    m2 = MAX_SPEED;
  if (m1 < -MAX_SPEED)
    m1 = -MAX_SPEED;
  if (m2 < -MAX_SPEED)
    m2 = -MAX_SPEED;
  speed1 = map(m1, -255, 255, 0, 255);
  speed2 = map(m2, -255, 255, 0, 255);
  if(!buttOn3)Enotik.send_message(2, (byte)speed1, (byte)speed2);  //*/
}

void loop() {
  Enotik.work();
  zahvat();
  line();
  int x = 0, y = 0, X1 = 0, Y1 = 0;
  for (int i = 0; i < FILTR_K; i++) {
    y += analogRead(axis_Y);
    x += analogRead(axis_X);
  }
  Y1 = (y / FILTR_K);
  X1 = (x / FILTR_K);

  Y1 = Y1 / 2 - 255;
  X1 = X1 / 2 - 255;
  if ((Y1 < FILTR_K) && (Y1 > -FILTR_K)) Y1 = 0;
  if ((X1 < FILTR_K) && (X1 > -FILTR_K)) X1 = 0;
  sendmotors(X1, Y1);
}
//   if ((digitalRead(2) == 0)&& !(flag)) {
//     /*Y1 = Y1+127;
//     X1 = X1;
//     //flag = 1;*/
//     Enotik.send_message(2,127,127);
//   }
//   if ((digitalRead(3) == 0)&& !(flag)) {
//     Y1 = Y1;
//     X1 = X1+127;
//     //sendmotors(127, 0);
//     //flag = 1;
//   }
//   if ((digitalRead(8/*4*/) == 0)&& !(flag)) {
//     Y1 = Y1-127;
//     X1 = X1;
//     //sendmotors(0, -127);
//     //flag = 1;
//   }
//   if ((digitalRead(5) == 0)&& !(flag)) {
//     Y1 = Y1;
//     X1 = X1-127;
//     //sendmotors(-127, 0);
//     //flag = 1;
//   }
//   //sendmotors(X1, Y1);
//   X1=0;
//   Y1=0;
//   flag=0;
// }