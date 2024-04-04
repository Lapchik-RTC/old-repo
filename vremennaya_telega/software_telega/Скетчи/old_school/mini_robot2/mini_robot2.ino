#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
//#include "motor.h"
#include "parser.h"
#include "Periph.h"
//#include "ryabina.h"

#define EN1 5
#define IN1 4
#define IN2 11
#define EN2 6
#define IN3 7
#define IN4 12

#define EN1_2 9
#define IN1_2 8
#define IN2_2 13

#define LEFT_SENSOR_PIN A1
#define RIGHT_SENSOR_PIN A0


#define LEFT 1
#define RIGHT 0

//определяется граница между черным и белым
#define BLACK 800

//константами задаются два варианта скоростей
#define FRW 240
#define BCK 0
//////////

void Drive_Normal(byte, byte);
void drive(int, int);
void drive2(byte, byte);
boolean lineSensor(int);

//////////
void setup() {
  Serial.begin(19200);
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
  if (v1>0){
   Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.println(analogRead(A0));
  
  //возможные сочетания цветов поля под датчиками
  //описано серией условий с использованием lineSensor(),
  //которая возвращает логическое значение, соответствующее черному или белому
  if(lineSensor(LEFT) && lineSensor(RIGHT))
  //в зависимости от сочетания цветов под датчиками
  //задается сочетание скоростей левого и правого колес
    drive(FRW,FRW);
  else if(lineSensor(LEFT) && !lineSensor(RIGHT))
    drive(FRW,BCK);
  else if(!lineSensor(LEFT) && lineSensor(RIGHT))
    drive(BCK,FRW);
  else
    drive(FRW,FRW);
  }

}


void drive(int left, int right)
{
  //left = constrain(left, -255, 255);
 // right = constrain(right, -255, 255);

  if (left >= 0){
    digitalWrite(IN3, HIGH);
  //  Serial.println("f");
  //digitalWrite(IN4, LOW);
  }
  else{
    digitalWrite(IN3, LOW);
 // digitalWrite(IN4, HIGH);
// Serial.println("fJ");
  }
  if (right >= 0){
    digitalWrite(IN1, HIGH);
 // digitalWrite(IN2, LOW);
// Serial.println("fP");
  }
  else{
    digitalWrite(IN1, LOW);
 // digitalWrite(IN2, HIGH);
 Serial.println("fG");
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


boolean lineSensor(int sensor)
{
  //в зависимости от того, какой датчик был запрошен
  //проверяется либо левый, либо правый датчик
  if(sensor == LEFT)
  {
     //в зависимости от того, превосходит ли значение,
     //полученное на датчике, пороговое значение
     //возвращается истина или ложь, т.е. "белое" или "черное"
     if(analogRead(LEFT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
  else if(sensor == RIGHT)
  {
     if(analogRead(RIGHT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
}
