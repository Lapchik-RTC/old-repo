#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
#define INA1 26
#define INB1 27
#define INA2 28
#define INB2 29
#define INA3 2
#define INB3 A0
#define PWM1 10
#define PWM2 9
#define PWM3 3

int vel1 = 0;
int vel2 = 0;
int vel3 = 0;
void motor(int vel, int motor);
double dist(double x1, double y1, double x2, double y2);
void findVs(int x, int y);
int* procesVs(int x, int y);
//void main(byte x, byte y);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(1, main1);
  Enotik.bind(2, main2);
  pinMode(INA1, 1);
  pinMode(INB1, 1);
  pinMode(PWM1, 1);
  pinMode(INA2, 1);
  pinMode(INB2, 1);
  pinMode(PWM2, 1);
  pinMode(INA3, 1);
  pinMode(INB3, 1);
  pinMode(PWM3, 1);
}
void motor(int motor, int vel) {
  int in1 = 0, in2 = 0, pwmPin = 0;
  /*int speed1 = 0;
  speed1 = map(vel, -255, 255, 0, 255);*/
  if (motor == 1) {
    in1 = INA1;
    in2 = INB1;
    pwmPin = PWM1;
  }
  if (motor == 2) {
    in1 = INA2;
    in2 = INB2;
    pwmPin = PWM2;
  }
  if (motor == 3) {
    in1 = INA3;
    in2 = INB3;
    pwmPin = PWM3;
  }

  ///

  digitalWrite(in1, !(vel >= 0));
  digitalWrite(in2, (vel > 0));

  /*Serial.print("\tm2: ");
  Serial.print(m2);
  Serial.print("\tm3: ");
  Serial.println(m3);

  for (int i = 0; i < motor; i++) {
    Serial.print('\t');
  }
  Serial.print("m1: ");
  Serial.println(vel_1);
  vel_1 = abs(vel_1);

*/
  analogWrite(pwmPin, vel);
}


double dist(double x1, double y1, double x2, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void findVs(int x, int y) {  //x, y -- координаты джостика
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
  Serial.print(v1);
  Serial.print("  ");
  Serial.print(v2);
  Serial.print("  ");
  Serial.println(v3);
  Serial.print("\n");
  //Serial.println(atan2(y, x));
  vel1 = v1;
  vel2 = v2;
  vel3 = v3;
  motor(1, vel1);
  motor(3, vel2);
  motor(2, vel3);
  delay(10);
}

int arr[] = { 0, 0, 0 };  //относится к функции ниже. А сама функция возвращает лишь ссылку на него

int* procesVs(int x, int y) {  //рассчёт НЕ конечных скоростей
  int v1 = 0;
  int v2 = 0;
  int v3 = 0;

  double alpha = 0;                         //потом задаётся
  double beta = 0;                          //120* - alpha
  int Vs = (dist(x, y, 0, 0) / 255) * 170;  //функция задания скорости порпорционально отклонению джостика
  if (Vs > 255) {
    Vs = 255;
  }
  int polozh;
  double anglePos = atan2(y, x);
  if (anglePos >= (-PI / 6) && anglePos <= (PI / 2)) {             // верх право
    polozh = 1;
    alpha = atan2(y, x) + (PI / 6);
  } else if (anglePos >= (-5 * PI / 6) && anglePos < (-PI / 6)) {  //низ
    polozh = 2;
    alpha = atan2(y, x) + (5 * PI / 6);
  } else if (anglePos > (PI / 2) && anglePos <= PI) {              //верх лево верх
    polozh = 3;
    alpha = atan2(y, x) - (PI / 2);
  } else {                                                         //верх лево низ
    polozh = 4;
    alpha = abs(-PI - atan2(y, x)) + (PI / 2);
  }
  beta = (TWO_PI / 3) - alpha;
  int Valpha = alpha / (TWO_PI / 3) * Vs;
  int Vbeta = beta / (TWO_PI / 3) * Vs;
  if (polozh == 1) {
    v3 = Vbeta;
    v1 = Valpha;
  } else if (polozh == 2) {
    v2 = Vbeta;
    v3 = Valpha;
  } else if (polozh == 3) {
    v1 = Vbeta;
    v2 = Valpha;
  } else {  //4 сектор, то есть polozh = 4;

    v1 = Vbeta;
    v2 = Valpha;
  }
  arr[0] = v1;
  arr[1] = v2;
  arr[2] = v3;
  // Serial.print("Valpha = ");
  // Serial.print(arr[0]);
  // Serial.print(" Vbeta ");
  // Serial.print(arr[1]);
  // Serial.print(" Vbeta2 ");
  // Serial.print(arr[2]);
  // Serial.println("\n");
  return arr;
}

void main2(byte e1, byte o) {
  int e = (int)e1;
  if(e == 2) {
  motor(1, 200);
  motor(2, 200);
  motor(3, 200);
  delay(10);
  }
  else if(e == 0) {
  motor(1, -200);
  motor(2, -200);
  motor(3, -200);
  delay(10);
  }
  // Serial.print( e);
}

void main1(byte x1, byte y1) {
  //////////////////////////////////////////
  int x2 = (int)x1;
  int y2 = (int)y1;
  int x = map(x2, 0, 255, -255, 255);
  int y = map(y2, 0, 255, -255, 255);
  Serial.print(x);
  Serial.print("  ");
  Serial.print(y);
  Serial.print("  ");
  //*/
  /*x = x * 2 - 255;
  y = y * 2 - 255;*/
  /////////////////////////////////////////



  /*int x = analogRead(A4);
  int y = analogRead(A5);*/
  //double doubles[] = { x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10, x11, y11, x12, y12 };
  // int bestInd = 0;
  //   double bestDist = dist(x, y, doubles[0], doubles[1]);
  //   double nowBD;

  if (abs(x) < 50 && abs(y) < 50) {
    motor(1, 0);
    motor(2, 0);
    motor(3, 0);

  }
  else {
    findVs(x, y);
  }
  Serial.println(" ");
  delay(10);
}

void loop() {
  Enotik.work();
}
/*if (vel_2 < STICK_LUFT && vel_2 > -STICK_LUFT) {
    v1_1 = 0;
    v2_1 = 0;
  }
  if (v2_1 < STICK_LUFT && v2_1 > -STICK_LUFT) {
    v1_1 = 0;
    v2_1 = 0;
  }*/
