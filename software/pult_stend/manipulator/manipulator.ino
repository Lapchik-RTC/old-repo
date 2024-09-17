#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
//#include "ryabina.h"
#include <Servo.h>
void manipulator(byte v1, byte v2);

void setup() {
  Serial1.begin(19200);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  // Enotik.bind(2, motor);
  //Enotik.bind(5, zahvat);
  //Enotik.bind(3, line);
  Enotik.bind(4, manipulator);
  // upserv.attach(3);
  // cserv.attach(2);
  // cserv.write(40);
  // //serv.attach(SERVO1_PIN);
  // pinMode(INA1, 1);
  // pinMode(INB1, 1);
  // pinMode(PWM1, 1);
  // pinMode(INA2, 1);
  // pinMode(INB2, 1);
  // pinMode(PWM2, 1);
}

double dist(double x1, double y1, double x2, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// int Vs[] = {0, 0, 0};

int vel1 = 0;
int vel2 = 0;
int vel3 = 0;

void findVs(int x, int y) {  //x, y  --  координаты джостика
  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
  int* Vplus = procesVs(x, y);  //скорости из реального положения джостика
  v1 += Vplus[0];
  v2 += Vplus[1];
  v3 += Vplus[2];
  int* Vminus = procesVs(-x, -y);  //скорости из противоположной точки, относительно реального положения джостика
  v1 -= Vminus[0];
  v2 -= Vminus[1];
  v3 -= Vminus[2];
  vel1 = v1;
  vel2 = v2;
  vel3 = v3;
}

int* procesVs(int x, int y) {  //рассчёт НЕ конечных скоростей
  int v1 = 0;
  int v2 = 0;
  int v3 = 0;

  double alpha = 0;                         //потом задаётся. Может, с помощью функции
  double beta = 0;                          //120* - alpha
  int Vs = (dist(x, y, 0, 0) / 255) * 255;  //функция задания скорости порпорционально отклонению джостика
  if (Vs > 255) {
    Vs = 255;
  }
  int polozh;
  double anglePos = atan2(x, y);
  if (anglePos >= (-PI / 6) && anglePos <= (PI / 2)) {  // верх право
    polozh = 1;
    alpha = atan2(x, y) + (PI / 6);
  } else if (anglePos >= (-5 * PI / 6) && anglePos < (-PI / 6)) {  //низ
    polozh = 2;
    alpha = atan2(x, y) - (PI / 6);
  } else if (anglePos > (PI / 2) && anglePos <= PI) {  //верх лево верх
    polozh = 3;
    alpha = atan2(x, y) + (5 * PI / 6);
  } else {  //верх лево низ
    polozh = 4;
    alpha = atan2(x, y) + (PI / 6);
  }
  beta = (TWO_PI / 3) - alpha;
  int Valpha = alpha / (2 * PI / 3) * Vs;
  int Vbeta = beta / (2 * PI / 3) * Vs;
  if (polozh == 1) {
    v1 = Vbeta;
    v3 = Valpha;
  } else if (polozh == 2) {
    v2 = Vbeta;
    v3 = Valpha;
  } else if (polozh == 3) {
    v2 = Vbeta;
    v1 = Valpha;
  } else {  //4 сектор, то есть polozh = 4;

    v1 = Vbeta;
    v2 = Valpha;
  }

  int arr[] = { v1, v2, v3 };
  return arr;
}
// double x1 = -512;
// double y1 = 0;
// double x2 = -512;
// double y2 = 512 * 0.57735026919;
// double x3 = -512 * 0.57735026919;
// double y3 = 512;
// double x4 = 0;
// double y4 = 512;
// double x5 = 512 * 0.57735026919;
// double y5 = 512;
// double x6 = 512;
// double y6 = 512 * 0.57735026919;
// double x7 = 512;
// double y7 = 0;
// double x8 = 512;
// double y8 = -512 * 0.57735026919;
// double x9 = 512 * 0.57735026919;
// double y9 = -512;
// double x10 = 0;
// double y10 = -512;
// double x11 = -512 * 0.57735026919;
// double y11 = -512;
// double x12 = -512;
// double y12 = -512 * 0.57735026919;

void manipulator(byte x1, byte y1) {
  int x = map(x1, 0, 255, 0, 1023);
  int y = map(y1, 0, 255, 0, 1023);
  Serial.print(x);
  Serial.print("\t");
  Serial.println(y);
  
  // Serial.println(x);
  // x = map(x1, 1, 1023, 1, 255);
  // Serial.println(x);
  //double doubles[] = { x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10, x11, y11, x12, y12 };
  // int bestInd = 0;
  //   double bestDist = dist(x, y, doubles[0], doubles[1]);
  //   double nowBD;
  if (abs(x) > 50 && abs(y) > 50) {
    findVs(x, y);
   // motor(1, vel1);
   // motor(2, vel2);
   // motor(3, vel3);
  }

  else {
    // motor(1, 0);
    // motor(2, 0);
    // motor(3, 0);
  }
  // Serial.println(vel1);
  delay(10);
}


void loop() {
  Enotik.work();
}
