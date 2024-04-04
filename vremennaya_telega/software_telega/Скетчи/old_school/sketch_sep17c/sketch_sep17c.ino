#include "Enotik.h"


void Pr (byte nc, byte b);
void setup() {
  Enotik.init_slave(0x04);
  Serial.begin(9600);
  Serial1.begin(9600);
  Enotik.bind(1, Pr);
}

void Pr (byte nc, byte b) {
 Serial.println(b);
}

void loop() {
  Enotik.work();

}
