#include <LiquidCrystal.h>
LiquidCrystal lcd (5, 4, 10, 11, 12, 13);
#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"


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

#define baton1 37
#define baton2 42
#define baton3 45
#define UP 40
#define CHANG 43
#define axis_X2 A9
#define axis_Y2 A10
#define SpeedStick A8
#define axis_X A11
#define axis_Y A12
#define axis_X3 A13
#define axis_Y3 A14


//////////////

int Y2 = 0;
int X2 = 0;
int y2 = 0;
int x2 = 0;
short int man1 = 90;
short int shvat1 = 80;
short int n = 31;
short int regim = 0;
int k = 0;
boolean gose = 0;
boolean back = 0;
boolean MicroBot = 0;
boolean MicroBotn = 0;
float ch = 0;

/////////////

void manipulator(int, int);
void sendmotors(int, int);
void sendmotors2(int, int);

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
  pinMode(A8, INPUT);
  lcd.createChar(0, Full);
  lcd.createChar(1, Mid);
  lcd.createChar(2, Low);
  lcd.begin(16, 2);
  for (int i = 1; i <= 9; i++) {
    pinMode(n, INPUT);
    n = n + 2;
  }
}

////////////

void loop()
{
  int y = 0;
  int x = 0;
  int Y1 = 0;
  int X1 = 0;
  int pr = 0;

  ch = analogRead(A7);
  ch = ch * 0.008300781;
  if(ch > 8) pr=0;
  else if(ch > 7.3 && ch<8) pr=1;
  else if(ch > 6.5 && ch<7.3) pr=2;
  for ( int i = 0; i < 10; i++) {
    y += analogRead(axis_Y);
    x += analogRead(axis_X);
  }
  Y1 = (y / 10);
  X1 = (x / 10);
  //Y1 = map(y, 1023, 0, -255, 255);
  //X1 = map(x, 1023, 0, -255, 255);
  Y1 = Y1 / 2 - 255;
  X1 = X1 / 2 - 255;
  if ((Y1 < 20) && (Y1 > -20))  Y1 = 0;
  if ((X1 < 20) && (X1 > -20))  X1 = 0;
  if (digitalRead(UP) == 1 && regim == 0) {
    while (digitalRead(UP) == 1) {}
    regim = 1;
  }
  if (digitalRead(UP) == 1 && regim == 1) {
    while (digitalRead(UP) == 1) {}
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

  if (regim == 1) {
    Enotik.send_message(7, 1,0);
  }
  else {
    Enotik.send_message(7, 0,0);
  }


  if (MicroBotn == 1 && MicroBot == 1) {
    sendmotors2(X1, Y1);
  }
  else {
    if (MicroBotn == 1 && MicroBot == 0) {
    lcd.setCursor(0, 1);
    lcd.print("error");
    }
    else{
    sendmotors(X1, Y1);
  }
  }

  Serial.print(map(analogRead(axis_X2), 0, 1023, -255, 255));
  Serial.print("     ");
  Serial.print(map(analogRead(axis_Y2), 0, 1023, -255, 255));
  Serial.print("     ");
  manipulator(map(analogRead(axis_X2), 0, 1023, -255, 255), map(analogRead(axis_Y2), 0, 1023, -255, 255));
  lcd.write(pr);
}





////////////
void sendmotors(int X1, int Y1) {
  if (MicroBotn == 0) {
    int m1 = 0;
    int m2 = 0;
    int speed1 = 0;
    int speed2 = 0;
    int speedValue = analogRead(A8);
    if (digitalRead(baton1) == 1 && MicroBot == 0) {
      while (digitalRead(baton1) == 1) {}
      MicroBot = 1;
    }
    if (digitalRead(baton1) == 1 && MicroBot == 1) {
      while (digitalRead(baton1) == 1) {}
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
      lcd.print("Mini");
    }
    else {
      Enotik.send_message(2, (byte)speed1, (byte)speed2);
      lcd.setCursor(0, 0);
      lcd.print("Big");
    }
    if (k == 6) {
      lcd.setCursor(0, 0);
      lcd.print("                 ");
      lcd.setCursor(0, 1);
      lcd.print("                 ");
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
  
  lcd.setCursor(0, 1);
  lcd.print(X1);
  lcd.setCursor(7, 1);
  lcd.print(Y1);

  Enotik.send_message(6, (byte)speed1, (byte)speed2);
  lcd.setCursor(0, 0);
  lcd.print("Track");
  if (k == 6) {
    lcd.setCursor(0, 0);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    k = 0;
  }
  k++;
}


////////////

void manipulator(int _X1, int _Y1) {
  if (MicroBot == 0) {
    if (_X1 > 240) {
      _X1 = 1;
    } else {
      if (_X1 < -240) {
        _X1 = -1;
      } else {
        _X1 = 0;
      }

    }
    if (_Y1 > 240) {
      _Y1 = 1;
    } else {
      if (_Y1 < -240) {
        _Y1 = -1;
      } else {
        _Y1 = 0;
      }
    }
    if (abs(_X1) < abs(_Y1)) {
      _X1 = 0;
    } else {
      if (abs(_X1) > abs(_Y1)) {
        _Y1 = 0;
      }
    }
    if (_X1 > 0) {
      if (shvat1 > 5) {
        shvat1--;
      }
      else {
        Enotik.send_message(5, (byte)man1, (byte)shvat1);  // man1=90 shvat=80->0
        // delay(10);
      }
      if ( _X1 < 0) {
        if (shvat1 < 80) {
          shvat1++;
        }
        Enotik.send_message(5, (byte)man1, (byte)shvat1);  // man1=90 shvat=80->0
        // delay(10);
      }    // delay(10);

    }
    if (_Y1 > 0) {
      if (man1 > 0) {
        man1--;
      }
      Enotik.send_message(5, (byte)man1, (byte)shvat1);  // man1=90 shvat=80->0
      // delay(10);

      //  delay(10);
    }
    if (_Y1 < 0) {
      if (man1 < 170) {
        man1++;
      }
      Enotik.send_message(5, (byte)man1, (byte)shvat1);  // man1=90 shvat=80->0
      // delay(10);
    }
    //  delay(10);
  }
}
