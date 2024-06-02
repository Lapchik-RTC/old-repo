#include"hodovaya.h"
void mymotor::attach(uint8_t ma, uint8_t mb, uint8_t pwmPin, uint8_t csPin, uint8_t encInterrPin, uint8_t encDirectPin, float kprop){
  pinMode(ma, 1);
  pinMode(mb, 1);
  pinMode(pwmPin, 1);
  pinMode(encInterrPin, 0);
  pinMode(encDirectPin, 0);
  _ma = ma;
  _mb = mb;
  _pwmPin = pwmPin;
  _csPin = csPin;
  _encInterrPin = encInterrPin;
  _encDirectPin = encDirectPin;
  _kprop = kprop;
}

void mymotor::power(int vel){
  digitalWrite(_ma, vel > 0);
  digitalWrite(_mb, vel < 0);
  vel = abs(vel);
  if(vel > 255) vel = 255;
  
  analogWrite(_pwmPin, vel);
}

// void mymotor::write(int speed){
//   //float kprop = 0.2;
//   static uint32_t oldTime = millis();
  
//   static float desireableEcn = 0;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);



//   int err = desireableEcn - _mEncoder;
  
  
//   // Serial.print(_mEncoder);
//   // Serial.print('\t');
//   // Serial.println(err);
//   power(err * _kprop);
//   oldTime = millis();
//   delay(10);
  
// }

// void mymotor::write2(int speed)
// {
//   //float kprop = 0.2;
//   static uint32_t oldTime = millis();
  
//   static float desireableEcn = 225;
//   int deltaT = millis() - oldTime;
//   desireableEcn += (speed * deltaT / 1000);

  

//   int err = desireableEcn - _mEncoder;
  
  
//   // Serial.print(_mEncoder);
//   // Serial.print('\t');
//   // Serial.println(err);
//   power(err * _kprop);
//   oldTime = millis();
//   delay(10); 
// }



void mymotor::statWrite(int val)
{
  static int velold = 0, err = 0;
  int enc_old = 0;
  float kv = 0.001, km = 0.2;
    err = val - ((_mEncoder - enc_old));
    enc_old = _mEncoder;
  power(err * km);
  delay(30);
  //Serial.println(_motorEnc);
}


////////////////////////////////////////
void mytelega::encSens()
{
    Serial.print("enc0: ");
    Serial.print(_motor0.getEnc());
    Serial.print("\tenc1: ");
    Serial.print(_motor1.getEnc());
    Serial.print("\tenc2: ");
    Serial.print(_motor2.getEnc());
    Serial.print("\tenc3: ");
    Serial.print(_motor3.getEnc());
    Serial.print("\tenc4: ");
    Serial.print(_motor4.getEnc());
    Serial.print("\tenc5: ");
    Serial.print(_motor5.getEnc());
    Serial.print("\n");
}

void mytelega::csSens()
{
  Serial.print("cs0: ");
    Serial.print(_motor0.getCS());
    Serial.print("\tcs1: ");
    Serial.print(_motor1.getCS());
    Serial.print("\tcs2: ");
    Serial.print(_motor2.getCS());
    Serial.print("\tcs3: ");
    Serial.print(_motor3.getCS());
    Serial.print("\tcs4: ");
    Serial.print(_motor4.getCS());
    Serial.print("\tcs5: ");
    Serial.print(_motor5.getCS());
    Serial.print("\n");
}