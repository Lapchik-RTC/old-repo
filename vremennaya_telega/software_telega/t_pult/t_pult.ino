#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"
#define axis_X A9
#define axis_Y A8

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_master(0x01);
  pinMode(axis_X, INPUT);
  pinMode(axis_Y, INPUT);
}
void sendmotors(int X1, int Y1){
    int m1 = 0;
    int m2 = 0;
    int speed1 = 0;
    int speed2 = 0;
    m1 = Y1 + X1;
    m2 = Y1 - X1;
    speed1 = map(m1, -255, 255, 0, 255);
    speed2 = map(m2, -255, 255, 0, 255);
    Enotik.send_message(2, (byte)speed1, (byte)speed2);
    Serial.print(m1);
    Serial.print(" ");
    Serial.println(m2);
}

void loop() {
  Enotik.work();
  int x=0, y=0, X1=0, Y1=0;
  for ( int i = 0; i < 10; i++) {
    y += analogRead(axis_Y);
    x += analogRead(axis_X);
  }
  Y1 = (y / 10);
  X1 = (x / 10);
  
  Y1 = Y1 / 2 - 255;
  X1 = X1 / 2 - 255;
  if ((Y1 < 20) && (Y1 > -20))  Y1 = 0;
  if ((X1 < 20) && (X1 > -20))  X1 = 0;
  sendmotors(X1, Y1);
}
