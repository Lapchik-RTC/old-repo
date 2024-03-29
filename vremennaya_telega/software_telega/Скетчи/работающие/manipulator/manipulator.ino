#include <Multiservo.h>
#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"


Multiservo ServoVN;
Multiservo Servo180;

void Manipulator2(byte, byte);

void setup() {
  Serial1.begin(19200);
  Serial.begin(9600);
  Servo180.attach(3);
  ServoVN.attach(5);
  Enotik.bind(5, Manipulator2);

}


void Manipulator2(byte man1, byte shvat1)
{
  Serial.println("servo");
  //Serial.println('Manipulator');
  //motor1.brake();
  //motor2.brake();
  int man = (int) man1;
  int shvat = (int) shvat1;

  if (shvat < -300) {
    shvat = -300;
  };

  if (shvat > 300) {
    shvat = 300;
  };
  if (man < -300) {
    man = -300;
  };
  if (man > 300) {
    man = 300;
  };
  Servo180.write(shvat);

  ServoVN.write(man);
};

void loop() {
  Enotik.work();
  motor1.work();
  motor2.work();
}
