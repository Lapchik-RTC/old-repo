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
#define MAX_SPEED 60
#define FILTR_K 20
int Z = 0;
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_master(0x01);
  pinMode(axis_X, INPUT);
  pinMode(axis_Y, INPUT);
}
void sendmotors(int X1, int Y1, int Z) {
  int m1 = 0;
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
    m1 = 0;
    m2 = 0;
    m3 = 0;
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
  speed1 = map(analogRead(A2), 0, 1023, 0, 255);
  speed2 = map(analogRead(A2), 0, 1023, 0, 255);
  speed3 = map(analogRead(A2), 0, 1023, 0, 255);
  /*Serial.print(speed1);
  Serial.print('\t');
  Serial.print(m2);
  Serial.print('\t');
  Serial.println(m3);*/
  Enotik.send_message(1, (byte)speed1, 1);
  Enotik.send_message(1, (byte)speed2, 2);
  Enotik.send_message(1, (byte)speed3, 3);
}


void loop() {
  Enotik.work();
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

  if ((analogRead(zbutt1) > 800) && Z == 0) {
    while ((analogRead(zbutt1) > 800)) {}
    Z = 1;
  }
  if ((analogRead(zbutt1) > 800) && Z == 1) {
    while ((analogRead(zbutt1) > 800)) {}
    Z = 0;
  }
  if ((analogRead(zbutt1) < 200) && Z == 0) {
    while ((analogRead(zbutt1) < 200)) {}
    Z = -1;
  }
  if ((analogRead(zbutt1) < 200) && Z == -1) {
    while ((analogRead(zbutt1) < 200)) {}
    Z = 0;
  }

  sendmotors(X1, Y1, Z);
}
