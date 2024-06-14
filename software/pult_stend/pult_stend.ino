#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"
#include <Servo.h>
// #define axis_X A9
// #define axis_Y A11
// #define zbutt1 A2
// #define MAX_SPEED 200
// #define FILTR_K 20
// int Z = 0;
void setup() {
  Serial1.begin(19200);
  Serial.begin(9600);
  Enotik.init_master(0x01);
  // pinMode(axis_X, INPUT);
  // pinMode(axis_Y, INPUT);
}

void sendmotors(int X, int Y) {
  /*int m1 = 0;
  int m2 = 0;
  int m3 = 0;
  int speed1 = 0;
  int speed2 = 0;
  int speed3 = 0;


  if (Z != 0) {
    m1 = MAX_SPEED * Z;
    m2 = MAX_SPEED * Z;
    m3 = MAX_SPEED * Z;
  } else {
    m1 = -Y*0.5;
    m2 = Y;
    m3=m1;
  }

  if (m1 > MAX_SPEED)
    m1 = MAX_SPEED;
  if (m1 < -MAX_SPEED)
    m1 = -MAX_SPEED;

  if (m2 > MAX_SPEED)
    m2 = MAX_SPEED;
  if (m2 < -MAX_SPEED)
    m2 = -MAX_SPEED;

  if (m3 > MAX_SPEED)
    m3 = MAX_SPEED;
  if (m3 < -MAX_SPEED) 
    m3 = -MAX_SPEED;
  speed1 = map(m1, -255, 255, 0, 255);
  speed2 = map(m2, -255, 255, 0, 255);
  speed3 = map(m3, -255, 255, 0, 255);
  Serial.print("m1: ");
  Serial.print(m1);
  Serial.print("\tm2: ");
  Serial.print(m2);
  Serial.print("\tm3: ");
  Serial.println(m3);*/

  Enotik.send_message(1, (byte)X, (byte)Y);
  //Serial.println(X);
  /*Enotik.send_message(1, (byte)speed2, 2);
  Enotik.send_message(1, (byte)speed3, 3);*/
}
void manipGo(int z){
  int z1 = map(z, -1, 1, 0, 2);
  //Serial.println(z1);
  Enotik.send_message(2, (byte)z1, (byte)0);
}

void loop() {
  Enotik.work();
//   int x = 0, y = 0, X1 = 0, Y1 = 0;
//   for (int i = 0; i < FILTR_K; i++) {
//     y += analogRead(axis_Y);
//     x += analogRead(axis_X);
//   }
//   Y1 = (y / FILTR_K);
//   X1 = (x / FILTR_K);

//   Y1 = Y1 / 2 - 255;
//   X1 = X1 / 2 - 255;
//   if ((Y1 < FILTR_K) && (Y1 > -FILTR_K)) Y1 = 0;
//   if ((X1 < FILTR_K) && (X1 > -FILTR_K)) X1 = 0;
// ////////////////////
//   if ((analogRead(zbutt1) > 800) && Z == 0) {
//     while ((analogRead(zbutt1) > 800)) {}
//     Z = 1;
//   }
//   if ((analogRead(zbutt1) > 800) && Z == 1) {
//     while ((analogRead(zbutt1) > 800)) {}
//     Z = 0;
//   }
//   if ((analogRead(zbutt1) < 200) && Z == 0) {
//     while ((analogRead(zbutt1) < 200)) {}
//     Z = -1;
//   }
//   if ((analogRead(zbutt1) < 200) && Z == -1) {
//     while ((analogRead(zbutt1) < 200)) {}
//     Z = 0;
//   }
//   Serial.print(X1);
//   Serial.print('\t');
//   Serial.println(Y1);
  
// /////////////
//   int xa = map(X1, -255, 255, 0, 255);
//   int ya = map(Y1, -255, 255, 0, 255);
//   //sendmotors(xa, ya);
  Enotik.send_message(1, 1/*(byte)xa*/, 1/*(byte)ya*/);
  //manipGo(Z);
  Serial.println(1);
}
/*
 
*/