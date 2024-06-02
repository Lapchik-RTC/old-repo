#include <Arduino.h>

//motor0
#define INA0 34
#define INB0 32
#define PWM0 4
#define CS0 A4

//motor1
#define INA1 37
#define INB1 39
#define PWM1 7
#define CS1 A3

//motor2
#define INA2 35//37
#define INB2 33//39
#define PWM2 5//7
#define CS2 A2//A3

//motor3
#define INA3 40
#define INB3 42
#define PWM3 8
#define CS3 A1

//motor4
#define INA4 38//40
#define INB4 36//42
#define PWM4 6//8
#define CS4 A0//A3

//motor5
#define INA5 41
#define INB5 43
#define PWM5 9
#define CS5 A5

volatile int encoder0 = 0;
volatile int encoder1 = 0;
volatile int encoder2 = 0;
volatile int encoder3 = 0;
volatile int encoder4 = 0;
volatile int encoder5 = 0;

void enc0()
{
  if(digitalRead(22))
    encoder0--;
  else
    encoder0++;
}
void enc1()
{
  if(digitalRead(23))
    encoder1--;
  else
    encoder1++;
}

void enc2()
{
  if(digitalRead(24))
    encoder2++;
  else
    encoder2--;
}

void enc3()
{
  if(digitalRead(25))
    encoder3--;
  else
    encoder3++;
}

void enc5()
{
  if(digitalRead(27))
    encoder5--;
  else
    encoder5++;
}
void enc4()
{
  if(digitalRead(26))
    encoder4++;
  else
    encoder4--;
}
//////////////////////////////////
void motorVal1(int val)
{
  digitalWrite(INB1, val > 0);
  digitalWrite(INA1, val < 0);
  val = abs(val);
  if(val > 255) val = 255;
  analogWrite(PWM1, val);
}

void motorVal3(int val)
{
  digitalWrite(INB3, val > 0);
  digitalWrite(INA3, val < 0);
  val = abs(val);
  if(val > 255) val = 255;
  analogWrite(PWM3, val);
}

void motorVal5(int val)
{
  digitalWrite(INB5, val > 0);
  digitalWrite(INA5, val < 0);
  val = abs(val);
  if(val > 255) val = 255;
  analogWrite(PWM5, val);
}
void motorVal0(int val)
{
  digitalWrite(INB0, val > 0);
  digitalWrite(INA0, val < 0);
  val = abs(val);
  if(val > 255) val = 255;
  analogWrite(PWM0, val);
}
void motorVal2(int val)
{
  digitalWrite(INB2, val > 0);
  digitalWrite(INA2, val < 0);
  val = abs(val);
  if(val > 255) val = 255;
  analogWrite(PWM2, val);
}
void motorVal4(int val)
{
  digitalWrite(INB4, val > 0);
  digitalWrite(INA4, val < 0);
  val = abs(val);
  if(val > 255) val = 255;
  analogWrite(PWM4, val);
}

void motorSpeed(int speed)
{
  float kprop = 0.5;
  static uint32_t oldTime = millis();
  // static uint32_t oldTime3 = millis();
  // static uint32_t oldTime5 = millis();
  //static uint32_t oldEncoder = encoder1;
  // static uint32_t oldEncoder3 = encoder3;
  // static uint32_t oldEncoder5 = encoder5;
  static float desireableEcn = 0;
  // static float desireableEcn3 = 0;
  // static float desireableEcn5 = 0;

  int deltaT = millis() - oldTime;
  desireableEcn += (speed * deltaT / 1000);

  int err = desireableEcn - encoder1;
  int err0 = desireableEcn - encoder0;
  int err2 = desireableEcn - encoder2;
  //int deltaT3 = millis() - oldTime3;
  
  int err3 = desireableEcn - encoder3;
  int err4 = desireableEcn - encoder4;
  //int deltaT5 = millis() - oldTime5;
  
  int err5 = desireableEcn - encoder5;
/*
  Serial.print("desireableEcn = ");
  Serial.print(desireableEcn);
  Serial.print('\t');
  Serial.print("encoder1 = ");
  Serial.print(encoder1);
  Serial.print('\t');
  Serial.print("err = ");+
  Serial.print(err);
  Serial.print('\n');*/
 motorVal1(err*kprop);
 motorVal0(err0*kprop);
 motorVal2(err2*kprop);
 motorVal3(err3*kprop);
 motorVal4(err4*kprop);
  motorVal5(err5*kprop);

  oldTime = millis();
  // oldTime3 = millis();
  // oldTime5 = millis();
  //oldEncoder = encoder1;

}

void setup() {
  pinMode(INA1, 1);
  pinMode(INB1, 1);
  pinMode(PWM1, 1);
  pinMode(INA3, 1);
  pinMode(INB3, 1);
  pinMode(PWM3, 1);
  pinMode(INA5, 1);
  pinMode(INB5, 1);
  pinMode(PWM5, 1);
  pinMode(INA0, 1);
  pinMode(INB0, 1);
  pinMode(PWM0, 1);
  pinMode(INA2, 1);
  pinMode(INB2, 1);
  pinMode(PWM2, 1);
  pinMode(INA4, 1);
  pinMode(INB4, 1);
  pinMode(PWM4, 1);
  pinMode(21, 0);
  pinMode(23, 0);
  pinMode(18,0);
  pinMode(25,0);
  pinMode(2,0);
  pinMode(27,0);

  pinMode(20, 0);
  pinMode(22, 0);
  pinMode(19,0);
  pinMode(24,0);
  pinMode(3,0);
  pinMode(26,0);
  
  attachInterrupt(digitalPinToInterrupt(21), enc1, RISING);
  attachInterrupt(digitalPinToInterrupt(18), enc3, RISING);
  attachInterrupt(digitalPinToInterrupt(19), enc2, RISING);
  attachInterrupt(digitalPinToInterrupt(2), enc5, RISING);
  attachInterrupt(digitalPinToInterrupt(20), enc0, RISING);
  attachInterrupt(digitalPinToInterrupt(3), enc4, RISING);
  Serial.begin(115200);
}



void loop() {
  static uint32_t oldTime = millis();
  motorSpeed(750);
  Serial.print("enc0");
  Serial.print(encoder0);
  Serial.print("\tenc1");
  Serial.print(encoder1);
  Serial.print("\tenc2");
  Serial.print(encoder2);
  Serial.print("\tenc3");
  Serial.print(encoder3);
  Serial.print("\tenc4");
  Serial.print(encoder4);
  Serial.print("\tenc5");
  Serial.print(encoder5);
  Serial.print("\n");
  delay(10);
}
