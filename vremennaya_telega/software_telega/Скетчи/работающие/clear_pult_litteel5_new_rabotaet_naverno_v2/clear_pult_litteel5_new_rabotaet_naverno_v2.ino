#include <LiquidCrystal.h>
LiquidCrystal lcd (5, 4, 10, 11, 12, 13);
#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"


//батарейка на дисплее 
byte Full[8] = {
  0b00110,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b00000,
};

byte Mid[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b01001,
  0b01111,
  0b01111,
  0b01111,
  0b00000,
};

byte Low[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01111,
  0b00000,
};


///////////////

#define baton1 39
#define baton2 42
#define baton3 45
#define baton4 40
#define baton5 43
#define CHANG 41
#define Close 47
#define axis_X2 A9
#define axis_Y2 A10
#define SpeedStick A8
#define axis_X A11
#define axis_Y A12
#define axis_X3 A13
#define axis_Y3 A14
#define sgat 46
#define rasgat 45

//////////////

int Y2 = 0;
int X2 = 0;
int y2 = 0;
int x2 = 0;
//short int man1 = 90;
short int shvat1 = 80;
//short int man2 = 90;
//short int shvat2 = 80;
//short int man3 = 90;
//short int shvat3 = 80;
short int back = 0;
short int n = 31;
short int regim = 0;
short int zahvat = 40;
short int pr=0;

int k = 0;
int stena = 0;
boolean gose = 0;
//boolean back = 0;
boolean MicroBot = 0;
boolean MicroBotn = 0;
int ch = 0;
boolean banka = 0;

/////////////

void manipulator(int);
void sendmotors(int, int);
void sendmotors2(int, int);
void sensor(byte, byte);

////////////

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_master(0x01);
  pinMode(axis_X, INPUT);
  pinMode(axis_Y, INPUT);
  pinMode(axis_X2, INPUT);
  pinMode(axis_Y2, INPUT);
  pinMode(axis_X3, INPUT);
  pinMode(axis_Y3, INPUT);
  pinMode(baton1, INPUT);
  pinMode(baton2, INPUT);
  pinMode(baton3, INPUT);
  pinMode(baton4, INPUT);
  pinMode(A8, INPUT);
  lcd.createChar(0, Full);
  lcd.createChar(1, Mid);
  lcd.createChar(2, Low);
  lcd.begin(16, 2);
  //Enotik.bind(9, sensor);
}

////////////

void loop()
{
  Enotik.work();
  // Serial.println(digitalRead(rasgat));
  int y = 0;
  int x = 0;
  int Y1 = 0;
  int X1 = 0;
  int pr = 0;
  ch = analogRead(A7);
  ch = ch * 0.008300781;
  if (ch > 8) pr = 0;
  else if (ch > 7.3 && ch < 8) pr = 1;
  else if (ch > 6.5 && ch < 7.3) pr = 2;
  for ( int i = 0; i < 10; i++) {
    y += analogRead(axis_Y);
    x += analogRead(axis_X);
  }
  lcd.setCursor(15,0);
    lcd.write(pr);
  Y1 = (y / 10);
  X1 = (x / 10);
  //Y1 = map(y, 1023, 0, -255, 255);
  //X1 = map(x, 1023, 0, -255, 255);
  Y1 = Y1 / 2 - 255;
  X1 = X1 / 2 - 255;
  if ((Y1 < 20) && (Y1 > -20))  Y1 = 0;
  if ((X1 < 20) && (X1 > -20))  X1 = 0;

//  Serial.print(digitalRead(baton1));
//  Serial.print(" ");
//  Serial.print(digitalRead(baton2));
//  Serial.print(" ");
//  Serial.print(digitalRead(baton3));
//  Serial.print(" ");
//  Serial.println(digitalRead(baton4));
//  
//  //Копия отладочная
//  if (digitalRead(baton1) == 1) {
//    Serial.print("If "), Serial.println(stena);
//    while (digitalRead(baton1) == 1) {}
//     Serial.print("While "),Serial.println(stena);
//    stena = 1;
//  }

  if (digitalRead(baton1) == 1 && stena == 0) {
    while (digitalRead(baton1) == 1) {}
    //Serial.println(stena);
    stena = 1;
  }
  if (digitalRead(baton1) == 1 && stena == 1) {
    while (digitalRead(baton1) == 1) {}
    stena = 0;
  }
  
  
  if (digitalRead(baton2) == 1 && regim == 0) {
    while (digitalRead(baton2) == 1) {}
    regim = 1;
  }
  if (digitalRead(baton2) == 1 && regim == 1) {
    while (digitalRead(baton2) == 1) {}
    regim = 0;
  }

  if (digitalRead(baton3) == 1 && MicroBotn == 0) {
    while (digitalRead(baton3) == 1) {}
    MicroBotn = 1;
  }
  if (digitalRead(baton3) == 1 && MicroBotn == 1) {
    while (digitalRead(baton3) == 1) {}
    MicroBotn = 0;
  }

    if (digitalRead(baton5) == 1 && MicroBot == 0) {
      while (digitalRead(baton5) == 1) {}
      MicroBot = 1;
    }
    if (digitalRead(baton5) == 1 && MicroBot == 1) {
      while (digitalRead(baton5) == 1) {}
      MicroBot = 0;
    }

       if (digitalRead(baton4) == 1 && banka == 0) {
      while (digitalRead(baton4) == 1) {}
      banka = 1;
    }
    if (digitalRead(baton4) == 1 && banka == 1) {
      while (digitalRead(baton4) == 1) {}
      banka = 0;
    }


  
  if (digitalRead(CHANG) == 1) {
    back++;
    delay(10);
    if (back > 126) back = 126;
    Enotik.send_message(9, (byte)back, 0);
    // Serial.println(back);
  }

  if (digitalRead(Close) == 1) {
    back--;
    delay(10);
    if (back < 40) back = 40;
    Enotik.send_message(9, (byte)back, 0);
    // Serial.println(back);
  }

  if (digitalRead(sgat) == 1) {
    if (zahvat == 100) {
      for (; zahvat > 40; zahvat--) {
        Enotik.send_message(10, (byte)zahvat, 0);
        delay(10);
      }
    }
    else if (zahvat == 40) {
      for (; zahvat < 100; zahvat++) {
        Enotik.send_message(10, (byte)zahvat, 0);
        delay(10);
      }
    }
    //Serial.println(zahvat);
  }



  if (regim == 1) {
    MicroBot = 0;
    lcd.setCursor(11, 1);
    lcd.print("line");
    Enotik.send_message(7, 1, 0);
  }
  else {
    Enotik.send_message(7, 0, 0);
  }


  if (stena == 1) {
    Enotik.send_message(11,0,1);
  }
  else {
    if (stena == 0) {
      Enotik.send_message(11,0,0);
      }
  }


  if (banka == 1) {
    Enotik.send_message(12,0,1);
  }
  else {
    if (banka == 0) {
      Enotik.send_message(12,0,0);
      }


  if (MicroBotn == 1 && MicroBot == 1) {
    sendmotors2(X1, Y1);
  }
  else {
    if (MicroBotn == 1 && MicroBot == 0) {
      lcd.setCursor(0, 1);
      lcd.print("error");
    }
    else {
      sendmotors(X1, Y1);
    }
  }

  manipulator(analogRead(axis_Y3)); //переход в функцию для манипулятора
 
  if (k == 50) {
    lcd.clear();
    k = 0;
  }
  k++;

  //Serial.print(map(analogRead(axis_X2), 0, 1023, -255, 255));
  //Serial.print("     ");
  //Serial.print(map(analogRead(axis_Y2), 0, 1023, -255, 255));
  //Serial.print("     ");
  //Enotik.send_message(2, 255, 255);
  
}
}

////////////



//void sensor(byte t, byte nichego) {
//  int k;
//  k = map(t, 0, 255, 3, 40);
//  lcd.setCursor(7, 0);
//  lcd.print(k);
//}



//////////// управление моторами
void sendmotors(int X1, int Y1) {
  if (MicroBotn == 0) {
    int m1 = 0;
    int m2 = 0;
    int speed1 = 0;
    int speed2 = 0;
    int speedValue = analogRead(A8);
    if (digitalRead(baton3) == 1 && MicroBot == 0) {
      while (digitalRead(baton3) == 1) {}
      MicroBot = 1;
    }
    if (digitalRead(baton3) == 1 && MicroBot == 1) {
      while (digitalRead(baton3) == 1) {}
      MicroBot = 0;
    }

    lcd.setCursor(11, 0);
    int u = analogRead(A8);
    u = map(u, 0, 1023, 0, 255);
    lcd.print(u);
    speedValue = map(speedValue, 0, 1023, 0, 255);
    m1 = Y1 + X1;
    m2 = Y1 - X1;
    if (m1 < -speedValue)
    {
      m1 = -speedValue;
    }
    if (m1 > speedValue)
    {
      m1 = speedValue;
    }
    if (m2 < -speedValue)
    {
      m2 = -speedValue;
    }
    if (m2 > speedValue)
    {
      m2 = speedValue;
    }

    speed1 = map(m1, -255, 255, 0, 255);
    speed2 = map(m2, -255, 255, 0, 255);
    lcd.setCursor(0, 1);
    lcd.print(m1);
    lcd.setCursor(5, 1);
    lcd.print(m2);
    if (MicroBot == 1) {
      Enotik.send_message(4, (byte)speed1, (byte)speed2);
      lcd.setCursor(0, 0);
      lcd.print( "Mini");
    }
    else {
      Enotik.send_message(2, (byte)speed1, (byte)speed2);
      lcd.setCursor(0, 0);
      lcd.print("Big");
    }
    if (k == 10) {
      lcd.clear();
      k = 0;
    }
    k++;
    
  }
}
////////////


void sendmotors2(int X1, int Y1) {
  int speed1 = 0;
  int speed2 = 0;
  //int speedValue = analogRead(A9);
  lcd.setCursor(11, 0);
  speed1 = map(X1, -255, 255, 0, 255);
  speed2 = map(Y1, -255, 255, 0, 255);
  if ((speed1 < 100) && (speed1 > -100))  speed1 = 0;
  if ((speed2 < 100) && (speed2 > -100))  speed2 = 0;

  if (k == 10) {
    lcd.clear();
    k = 0;
  }
  k++;

  lcd.setCursor(0, 1);
  lcd.print(X1);
  lcd.setCursor(7, 1);
  lcd.print(Y1);
  if (k == 100) {
    lcd.clear();
    k = 0;
  }
  k++;

  Enotik.send_message(6, (byte)speed1, (byte)speed2);
  lcd.setCursor(0, 0);
  lcd.print("Track");
  if (k == 20) {
    lcd.clear();
    k = 0;
  }
  k++;
}


////////////
//от 40 до 115 или 116
void manipulator(int _X1)
{
  _X1 = map(_X1, 0, 1023, -255, 255);
  //Serial.print(_X1);
  //Serial.print("  ");
  // Serial.print(MicroBot);
  if (MicroBot == 0)
  {
    if (_X1 > 200) {
      shvat1++;
    }
    else
    {
      if (_X1 < -200)
      {
        shvat1--;
      }

    }
    if (shvat1 > 150) {
      shvat1 = 150;
    }
    if (shvat1 < 85) {
      shvat1 = 85;  
    }
    Enotik.send_message(8, (byte)shvat1, 0);
  }
  //Serial.println(shvat1);
  delay(10);
}
