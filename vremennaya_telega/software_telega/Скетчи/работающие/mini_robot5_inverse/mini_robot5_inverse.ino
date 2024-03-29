#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
//#include "motor.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"

#define EN1 6
#define IN1 5
#define IN2 7
#define EN2 2
#define IN3 3
#define IN4 4
#define LEFT_SENSOR_PIN A4
#define RIGHT_SENSOR_PIN A5

#define EN1_2 11
#define IN1_2 13
#define IN2_2 12

#define EN2_2 9
#define IN3_2 10
#define IN4_2 8

#define LEFT 1
#define RIGHT 0
#define BLACK 500


#define FRW 240
#define BCK -140

///////////

int perekr = 0;

//////////

void Drive_Normal(byte, byte);
void drive_g(byte, byte);
void drive(int, int);
void drive_x(int, int);
void drive2(byte, byte);
boolean lineSensor(int sensor);
void drive(int left, int right);
void line(byte test, byte nichego);
boolean lineSensor_inverse(int sensor);

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
  Enotik.bind(5, drive2);
  Enotik.bind(4, Drive_Normal);
  Enotik.bind(6, drive_g);
  Enotik.bind(7, line);
}

/////////

void loop() {
  Enotik.work();
  //motor1.work();
  //motor2.work();
  
}


void drive_g(byte vc1, byte vc2)
{
  //Serial1.println(v1);
  int v1_1 = (int) vc1;
  int v2_1 = (int) vc2;
  v1_1 = v1_1 * 2 - 255;
  v2_1 = v2_1 * 2 - 255;
  drive_x(v1_1, v2_1);
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
 
void drive2(byte right, byte nicego)
{
  //int t = (int) right;
  //t = map(t, 0 , 255, -255, 255);

  // t = constrain(right, -255, 255);

  if (right == 255) {
    digitalWrite(IN1_2, HIGH);
    digitalWrite(IN2_2, LOW);
    digitalWrite(IN3_2, HIGH);
    digitalWrite(IN4_2, LOW);
    Serial.println("1");
  }
  else {
    if (right == 1) {
      digitalWrite(IN1_2, LOW);
      digitalWrite(IN2_2, HIGH);
      digitalWrite(IN3_2, LOW);
      digitalWrite(IN4_2, HIGH);
      Serial.println("2");
    }
    else {
      if (right == 0) {
        digitalWrite(IN1_2, LOW);
        digitalWrite(IN2_2, LOW);
        digitalWrite(IN3_2, LOW);
        digitalWrite(IN4_2, LOW);
      }
    }
  }

  analogWrite(EN1_2, 255);
  analogWrite(EN2_2, 255);

}


void drive_x(int left, int right)
{
  if (left <= 255 && left >= 100) {
    digitalWrite(IN3_2, HIGH);
    //  Serial1.println("f");
    analogWrite(IN4_2, 0);
    digitalWrite(IN1_2, LOW);
    analogWrite(IN2_2, 0);
  }
  else {
    if (left >= -255 && left <= -100) {
      digitalWrite(IN3_2, LOW);
      analogWrite(IN4_2, 255);
      //Serial1.println("fJ");
      digitalWrite(IN1_2, LOW);
      analogWrite(IN2_2, 0);
    }
    else {
      digitalWrite(IN3_2, LOW);
      analogWrite(IN4_2, 0);
    }
  }
  if (right <= 255 && right >= 100) {
    digitalWrite(IN1_2, HIGH);
    analogWrite(IN2_2, 0);
    //Serial.println("fP");
  }
  else {
    if (right >= -255 && right <= -100) {
      digitalWrite(IN1_2, LOW);
      analogWrite(IN2_2, 255);
      //Serial.println("fG");
    }
    else {
      digitalWrite(IN2_2, LOW);
      analogWrite(IN1_2, 0);
    }
  }
  analogWrite(EN2_2, 255);
  analogWrite(EN1_2, 225);

}


void drive_inverse(int left, int right)
{
  //left = constrain(left, -255, 255);
  // right = constrain(right, -255, 255);

  if (left >= 0) {
    digitalWrite(IN3, 0);
    //  Serial1.println("f");
    analogWrite(IN4, HIGH);
  }
  else {
    digitalWrite(IN3, HIGH);
    analogWrite(IN4, 0);
    //Serial1.println("fJ");
  }
  if (right >= 0) {
    digitalWrite(IN1, LOW);
    analogWrite(IN2, 255);
    //Serial.println("fP");
  }
  else {
    digitalWrite(IN1, HIGH);
    analogWrite(IN2, 0);
    //Serial.println("fG");
  }
  analogWrite(EN2, abs(left));
  analogWrite(EN1, abs(right));

}

void line(byte test, byte nichego){
  if (test == 1){
      Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.println(analogRead(A0));
  
  //возможные сочетания цветов поля под датчиками
  //описано серией условий с использованием lineSensor(),
  //которая возвращает логическое значение, соответствующее черному или белому
  if(lineSensor_inverse(LEFT) && lineSensor_inverse(RIGHT))
  //в зависимости от сочетания цветов под датчиками
  //задается сочетание скоростей левого и правого колес
    drive(FRW,FRW);
  else if(lineSensor_inverse(LEFT) && !lineSensor_inverse(RIGHT))
    drive(FRW,BCK);
  else if(!lineSensor_inverse(LEFT) && lineSensor_inverse(RIGHT))
    drive(BCK,FRW);
  else
    drive(FRW,FRW);

    
   if(lineSensor_inverse(LEFT) && lineSensor_inverse(RIGHT))
{  
  Serial.println("inverse"); 
   {
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
  
}
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



boolean lineSensor_inverse(int sensor)
{
  //в зависимости от того, какой датчик был запрошен
  //проверяется либо левый, либо правый датчик
  if(sensor == LEFT)
  {
     //в зависимости от того, превосходит ли значение,
     //полученное на датчике, пороговое значение
     //возвращается истина или ложь, т.е. "белое" или "черное"
     if(analogRead(RIGHT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
  else if(sensor == RIGHT)
  {
     if(analogRead(LEFT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
}
