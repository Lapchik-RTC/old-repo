#include <Arduino.h>
#include <crc8.h>
#include <Enotik.h>
#include <enotik_master.h>
#include <Enotik_message_format.h>
#include <parser.h>
#include <Periph.h>
#include <drive.h>


//motor0
#define INA0 34
#define INB0 32
#define PWM0 4
#define CS0 A4
//motor1
#define INA1 37//35
#define INB1 39//33
#define PWM1 7//5
#define CS1 A3//A2
//motor2
#define INA2 35//37
#define INB2 33//39
#define PWM2 5//7
#define CS2 A2//A3
//motor3
#define INA3 40//38
#define INB3 42//36
#define PWM3 8//6
#define CS3 A1//A0
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

#define MOTOR_LENGTH (sizeof(motor)/sizeof(motor[0]))

mymotor motor[6];
int32_t motorEncs[6];
float tpsMax = 800, motorK = 2, motorKi = 0.01;
int16_t vMotor[6]; 
/*
* motor0 -
* motor1 pc
* motor2 lc+
* motor3 pb+
* motor4 pf+
* motor5 -
*/

const uint8_t interrupts[] = {20, 21, 19, 18, 3, 2 };//{ 20, 19, 18, 2, 3, 2 };

const uint8_t reverses[] = { 1, 0, 1, 0, 1, 0 };

const uint8_t directionPins[] = {22, 23, 24, 25, 26, 27 };//{ 22, 24, 25, 1, 26, 27 };


void encoder0(){
  if(digitalRead(directionPins[0]))
  motorEncs[0]--;
  else
  motorEncs[0]++;
}
void encoder1(){
  if(digitalRead(directionPins[1]))
  motorEncs[1]--;
  else
  motorEncs[1]++;
}
void encoder2(){
  if(digitalRead(directionPins[2]))
  motorEncs[2]--;
  else
  motorEncs[2]++;
}
void encoder3(){
  if(digitalRead(directionPins[3]))
  motorEncs[3]--;
  else
  motorEncs[3]++;
}
void encoder4(){
  if(digitalRead(directionPins[4]))
  motorEncs[4]--;
  else
  motorEncs[4]++;
}
void encoder5(){
  if(digitalRead(directionPins[5]))
  motorEncs[5]--;
  else
  motorEncs[5]++;
}

/*
// void interr0() {
//   motorEncs[0] = motorEncs[0] - (reverses[0] * 2 - 1) * (digitalRead(directionPins[0]) * 2 - 1);
// }

// void interr1() {
//   motorEncs[1] = motorEncs[1] - (reverses[1] * 2 - 1) * (digitalRead(directionPins[1]) * 2 - 1);
// }

// void interr2() {
//   motorEncs[2] = motorEncs[2] - (reverses[2] * 2 - 1) * (digitalRead(directionPins[2]) * 2 - 1);
// }

// void interr3() {
//   motorEncs[3] = motorEncs[3] - (reverses[3] * 2 - 1) * (digitalRead(directionPins[3]) * 2 - 1);
// }

// void interr4() {
//   motorEncs[4] = motorEncs[4] - (reverses[4] * 2 - 1) * (digitalRead(directionPins[4]) * 2 - 1);
// }

// void interr5() {
//   motorEncs[5] = motorEncs[5] - (reverses[5] * 2 - 1) * (digitalRead(directionPins[5]) * 2 - 1);
// }
*/

void setup() {
  Serial.begin(9600);
  Serial3.begin(250000);
  
  motor[0].attach(INA0, INB0, PWM0, CS0, tpsMax, motorK, motorKi);
  motor[1].attach(INA1, INB1, PWM1, CS1, tpsMax, motorK, motorKi);
  motor[2].attach(INA2, INB2, PWM2, CS2, tpsMax, motorK, motorKi);
  motor[3].attach(INA3, INB3, PWM3, CS3, tpsMax, motorK, motorKi);
  motor[4].attach(INA4, INB4, PWM4, CS4, tpsMax, motorK, motorKi);
  motor[5].attach(INA5, INB5, PWM5, CS5, tpsMax, motorK, motorKi);

  /*
  pinMode(directionPins[0], 0);
  pinMode(directionPins[1], 0);
  pinMode(directionPins[2], 0);
  pinMode(directionPins[3], 0);
  pinMode(directionPins[4], 0);
  pinMode(directionPins[5], 0);

  pinMode(interrupts[0], 0);
  pinMode(interrupts[1], 0);
  pinMode(interrupts[2], 0);
  pinMode(interrupts[3], 0);
  pinMode(interrupts[4], 0);
  pinMode(interrupts[5], 0);
  */
  
  for(int i = 0; i < MOTOR_LENGTH; i++){
    pinMode(directionPins[i], 0);
    pinMode(interrupts[i], 0);
  }

  Enotik.init_slave(0x01);

  attachInterrupt(digitalPinToInterrupt(interrupts[0]), encoder0, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupts[1]), encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupts[2]), encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupts[3]), encoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupts[4]), encoder4, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupts[5]), encoder5, RISING);

  //vMotor[1] = vMotor[3] = vMotor[5] = 0;

}

// void mSin(int vel){
//   int ms[MOTOR_LENGTH];
//   int speedPerf = 0;
//   for(int i = 0; i < MOTOR_LENGTH; i++){
//     //motor[i].setVel(vel);
//     motor[i].setEnc(motorEncs[i]);
//     ms[i] = motor[i].getSpeed();
//   }
//   // int pu[4] = {0,0,0,0};
//   // for(int i; i<3; i++){
//     //находим большую скорость из 3
//     if(ms[1]>speedPerf){speedPerf = ms[1];}
//     if(ms[3]>speedPerf){speedPerf = ms[3];}
//     if(ms[5]>speedPerf){speedPerf = ms[5];}  
//     //pu[i] = speedPerf;
//   // }
//   // for (int j = 0; j < 2; j++)//пузырьковый фильлтр
//   //    for (int i = 0; i < 2; i++)
//   //      if ( pu[i] > pu[i + 1])
//   //      {
//   //       pu[3] = pu[i];
//   //       pu[i] = pu[i + 1];
//   //       pu[i + 1] = pu[3];
//   //     }
//   // speedPerf = pu[0];
//   //если мотор крутится нормально то f будет равна 0 и нужно подавать просто vel иначе умножаем vel на разность скоростей_Х10
  
//   if(((speedPerf-ms[1])*10) == 0){motor[1].setVel(vel);}
//   else{motor[1].setVel(vel*((speedPerf-ms[5])));}

//   if(((speedPerf-ms[3])*10) == 0){motor[3].setVel(vel);}
//   else{motor[3].setVel(vel*((speedPerf-ms[5])));}
  
//   if(((speedPerf-ms[5])*10) == 0){motor[5].setVel(vel);}
//   else{motor[5].setVel(vel*((speedPerf-ms[5])));}

  
//   // motor[1].setVel(vel*(ms[1]/speedPerf));
//   // motor[3].setVel(vel*(ms[3]/speedPerf));
//   // motor[5].setVel(vel*(ms[5]/speedPerf));

//   motorEncs[1] = 0;
//   motorEncs[3] = 0;
//   motorEncs[5] = 0;
//   motor[1].resetTime();
//   motor[3].resetTime();
//   motor[5].resetTime();

//   motor[1].write();
//   motor[3].write();
//   motor[5].write();
  
//   Serial.print("m1: ");
//   Serial.print(vel*((speedPerf-ms[1])));
//   Serial.print("\tm3: ");
//   Serial.print(vel*((speedPerf-ms[3])));
//   Serial.print("\tm5: ");
//   Serial.print(vel*((speedPerf-ms[5])));

//   Serial.print("\t\tms1/sp: ");
//   Serial.print(ms[1]/speedPerf);
//   Serial.print("\tms3/sp: ");
//   Serial.print(ms[3]/speedPerf);
//   Serial.print("\tms5/sp: ");
//   Serial.print(ms[5]/speedPerf);
  
//   Serial.print("\t\tsP: ");
//   Serial.print(speedPerf);

//   Serial.print("\t\tenc1: ");
//   Serial.print(motorEncs[1]);
//   Serial.print("\t\tenc3: ");
//   Serial.print(motorEncs[3]);
//   Serial.print("\t\tenc5: ");
//   Serial.print(motorEncs[5]);
//   Serial.println(); 
// }

void loop(){
  // mSin(10);
  // delay(10);
  int v = 100;
  motor[1].setEnc(motorEncs[1]);
  motor[1].write(v);
  
  motor[3].setEnc(motorEncs[3]);
  motor[3].write(v);
  //Serial.println(motorEncs[1]);
  
}
/*
* motor0 -
* motor1 pc
* motor2 lc+
* motor3 pb+
* motor4 pf+
* motor5 -
*
* minEncSpeed = +-80
*/