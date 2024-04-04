#include <LiquidCrystal.h>
LiquidCrystal lcd (4, 5, 10, 11, 12, 13);
#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
//#include "motor.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"

///////////////

#define baton1 A11
#define baton2 A3
#define UP 33
#define CHANG 31
#define axis_X A8
#define axis_Y A10
#define SpeedStick A9
#define axis_X2 A5
#define axis_Y2 A4

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


/////////////

void manipulator(int, int);
void sendmotors(int, int);
void goose(int, int, int, int);

////////////

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_master(0x01);
  pinMode(axis_X, INPUT);
  pinMode(axis_Y, INPUT);
  pinMode(baton1, INPUT);
  pinMode(baton2, INPUT);
  pinMode(A9, INPUT);
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
  if (digitalRead(baton1) == 0 && gose == 0) {
    while (digitalRead(baton1) == 0) {}
    gose = 1;
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

    sendmotors(X1, Y1);

    Serial.print(map(analogRead(axis_X2), 0, 1023, -255, 255));
    Serial.print("     ");
    Serial.print(map(analogRead(axis_Y2), 0, 1023, -255, 255));
    Serial.print("     ");
    manipulator(map(analogRead(axis_X2), 0, 1023, -255, 255), map(analogRead(axis_Y2), 0, 1023, -255, 255));
    //Enotik.send_message(2, 255, 255);
  }
  if (digitalRead(baton1) == 0 && gose == 1) {
    while (digitalRead(baton1) == 0) {}
    gose = 0;
    int _Y = map(analogRead(axis_X), 0, 1023, -255, 255);
    int _X = map(analogRead(axis_Y), 0, 1023, -255, 255);
    int _Y1 = map(analogRead(axis_X2), 0, 1023, -255, 255);
    int _X1 = map(analogRead(axis_Y2), 0, 1023, -255, 255);
     goose(_Y, _X, _Y1, _X1);

  }
}


////////////

void sendmotors(int X1, int Y1) {
  int m1 = 0;
  int m2 = 0;
  int speed1 = 0;
  int speed2 = 0;
  int speedValue = analogRead(A9);
  lcd.setCursor(11, 0);
  int u = analogRead(A9);
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
  lcd.setCursor(7, 1);
  lcd.print(m2);
  Enotik.send_message(2, (byte)speed1, (byte)speed2);
  if (k == 5) {
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
    Enotik.send_message(3, (byte)man1, (byte)shvat1);  // man1=90 shvat=80->0
    // delay(10);
  }
  if ( _X1 < 0) {
    if (shvat1 < 80) {
      shvat1++;
    }
    Enotik.send_message(3, (byte)man1, (byte)shvat1);
    // delay(10);

  }
  if (_Y1 > 0) {
    if (man1 > 0) {
      man1--;
    }
    Enotik.send_message(3, (byte)man1, (byte)shvat1); // man1=90->0 shvat=80
    //  delay(10);
  }
  if (_Y1 < 0) {
    if (man1 < 170) {
      man1++;
    }
    Enotik.send_message(3, (byte)man1, (byte)shvat1);
    //  delay(10);
  }

  Serial.print(byte(man1));
  Serial.print("   ");
  Serial.println(byte(shvat1));
  delay(50);
}


void goose(int _X1, int _Y1, int _X2, int _Y2) {
  int shvat2;
  int man2;

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
  if (_X2 > 240) {
    _X2 = 1;
  } else {
    if (_X2 < -240) {
      _X2 = -1;
    } else {
      _X2 = 0;
    }

  }
  if (_Y2 > 240) {
    _Y2 = 1;
  } else {
    if (_Y2 < -240) {
      _Y2 = -1;
    } else {
      _Y2 = 0;
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
    Enotik.send_message(4, (byte)man1, (byte)shvat1);  // man1=90 shvat=80->0
    // delay(10);
  }
  if ( _X1 < 0) {
    if (shvat1 < 80) {
      shvat1++;
    }
    Enotik.send_message(4, (byte)man1, (byte)shvat1);
    // delay(10);

  }
  if (_Y1 > 0) {
    if (man1 > 0) {
      man1--;
    }
    Enotik.send_message(4, (byte)man1, (byte)shvat1); // man1=90->0 shvat=80
    //  delay(10);
  }
  if (_Y1 < 0) {
    if (man1 < 170) {
      man1++;
    }
    Enotik.send_message(4, (byte)man1, (byte)shvat1);
    //  delay(10);
  }
  if (abs(_X2) < abs(_Y2)) {
    _X2 = 0;
  } else {
    if (abs(_X2) > abs(_Y2)) {
      _Y2 = 0;
    }
  }
  if (_X2 > 0) {
    if (shvat2 > 5) {
      shvat2--;
    }
    Enotik.send_message(5, (byte)man2, (byte)shvat2);  // man1=90 shvat=80->0
    // delay(10);
  }
  if ( _X2 < 0) {
    if (shvat2 < 80) {
      shvat2++;
    }
    Enotik.send_message(5, (byte)man2, (byte)shvat2);
    // delay(10);

  }
  if (_Y2 > 0) {
    if (man2 > 0) {
      man2--;
    }
    Enotik.send_message(5, (byte)man2, (byte)shvat2); // man1=90->0 shvat=80
    //  delay(10);
  }
  if (_Y2 < 0) {
    if (man2 < 170) {
      man2++;
    }
    Enotik.send_message(5, (byte)man2, (byte)shvat2);
    //  delay(10);
  }

  Serial.print(byte(man1));
  Serial.print("   ");
  Serial.println(byte(shvat1));
  delay(50);
}
