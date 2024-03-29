#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
//#include "motor.h"
#include "parser.h"
#include "Periph.h"
//#include "ryabina.h"
#include <Servo.h>


//обьявление портов для управления моторами3
#define EN1 5
#define IN1 7
#define IN2 8
#define EN2 6
#define IN3 4
#define IN4 9

//объявление переменных для автономных участков
#define V 100
#define S 30
//#define MS1 5
//#define MS2 6
#define SHARP A14
#define Kp 2
#define Ki 0
#define Kd 0
#define MS 10
//#define Rellay 8
#define SHARPPIN A15
//#define LED 45
//////////////

//сервы
Servo ServoVN;
Servo ServoZAHVAT;
Servo Servo180;
Servo ServoUp1;
Servo ServoUp2;
Servo MS3;
//Servo ServoShvatUp;


//вспомагательные переменные
int eOld;
int p;
int d;
//////////////

//для управления манипулятором
void Manipulator2(byte, byte);
void Manipulator3(byte, byte);
void Manipulator1(byte, byte);

//для управления моторами
void Drive_Normal(byte, byte);
void stop_motor();
void drive(int, int);

//для автономныхучастков
void do_banki();
//void Stena();
//void Regulator1();

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(2, Drive_Normal);
  Enotik.bind(8, Manipulator2);
  Enotik.bind(9, Manipulator1);
  Enotik.bind(10, Manipulator3);
  Enotik.bind(12, do_banki);
 // Enotik.bind(11, Stena);

  pinMode(SHARP, INPUT);
  pinMode(SHARPPIN, INPUT);
  pinMode (EN1, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (EN2, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (IN3, OUTPUT);




  //ServoZAHVAT.attach(2);
  Servo180.attach(13);
  ServoVN.attach(12);
  ServoZAHVAT.attach(11);
  ServoUp2.attach(2);
  ServoUp1.attach(3);
  MS3.attach(MS);
  ServoVN.write(150);
  MS3.write(10);
}

void loop() {
  Enotik.work();
}

/////////////auto

////регулятор для движения по стене
//int Regulator1 (int Ustavka, int Znachenie)
//{
//  //Serial.println(Znachenie);
//  int u;
//  int er;
//  unsigned long now = millis();
//  unsigned long lastTime;
//  double DeltaTime = (double) ( now - lastTime );
//  er = Ustavka - Znachenie;
//  p = er * -Kp;
//  d = Kd * ((er - eOld) / DeltaTime);
//  u = p + d;
//  //u = map(u, -1023, 1023, -100, 100);
//  eOld = er;
//  lastTime = now;
//  //Serial.println(u);
//  //delay(100);
//  return u;
//}
//
////для движения по стене, тут происходит полнейший бред (моторы страшно гудят и работают по не понятному алгоритму)
//void Stena (byte nichego, byte K)
//{
//  MS3.write(0);
//  //Serial.println('Stena');
//  int _K = (int) K;
//  int perevod;
//  if (_K == 1)
//  {
//    int volts = analogRead(SHARP);   //0.0048828125;
//    int i = constrain(volts, 40, 650);
//    int z = (6787/(i-3))-4; 
//    //Serial.println(volts);
//    //ServoSHARP.write(150);
//    drive(V - Regulator1(S, volts), V + Regulator1(S, volts));//переходы в функцию регулятора
//    //Serial.println(_K);
//  }
//  else{
//      MS3.write(25);
//  }
//}



//движение до банки, тут происходит какой-то бред (манипулятор не захватывает)
void do_banki(byte nichego, byte r) {
  if (r == 1) {
    int zn = analogRead(SHARPPIN);
    while (zn < 530) {
      zn = analogRead(SHARPPIN);
      //Serial.println(zn);
      drive(30, 30);
      if (zn >= 530) {
       // Serial.println(zn);
        ServoZAHVAT.write(90);
        break;
      }
      
    }
  }
}


//кусок управления манипулятором, оно работает стабильно
void Manipulator2(byte shvat1, byte man1)
{
  //Serial.println("servo");
  //Serial.println('Manipulator');
  //motor1.brake();
  //motor2.brake();
  int shvat = (int) shvat1;

  if (shvat < -300) {
    shvat = -300;
  }

  if (shvat > 300) {
    shvat = 300;
  }
  ServoVN.write(shvat);

}



void Manipulator1(byte man3, byte nichego)
{
  stop_motor();
  int man = (int) man3;
  if (man < -300) {
    man = -300;
  }
  if (man > 300) {
    man = 300;
  }
  ServoUp1.write(man);
  delay(10);
 
}



void Manipulator3(byte man2, byte shvat2)
{
  stop_motor();
  int man = (int) man2;

  if (man < -300) {
    man = -300;
  }
  if (man > 300) {
    man = 300;
  }
  ServoZAHVAT.write(man);
};



//управление моторами, тут вроде все нормально
void Drive_Normal(byte v1, byte v2)
{
  //Serial.println('Drive_n');
  int v1_1 = (int) v1;
  int v2_1 = (int) v2;
  v1_1 = v1_1 * 2 - 255;
  v2_1 = v2_1 * 2 - 255;
  if (v1_1 < 10 && v1_1 > -10) {
    stop_motor();
  }
  if (v2_1 < 10 && v2_1 > -10) {
    stop_motor();
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

  if (left >= 0) {
    digitalWrite(IN3, HIGH);
    //  Serial1.println("f");
    analogWrite(IN4, 0);
  }
  else {
    digitalWrite(IN3, LOW);
    analogWrite(IN4, 255);
    //Serial1.println("fJ");
  }
  if (right >= 0) {
    digitalWrite(IN1, HIGH);
    analogWrite(IN2, 0);
    //Serial.println("fP");
  }
  else {
    digitalWrite(IN1, LOW);
    analogWrite(IN2, 255);
    //Serial.println("fG");
  }
  analogWrite(EN2, abs(left));
  analogWrite(EN1, abs(right));
}


void stop_motor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
