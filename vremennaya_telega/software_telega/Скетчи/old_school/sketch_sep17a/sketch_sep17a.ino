#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
//#include "motor.h"
#include "parser.h"
#include "Periph.h"
//#include "ryabina.h"
void setup() {
  Enotik.init_master(0x01);
  Serial1.begin(9600);

}

void loop() {
   for (int i=0; i<256; i++)
  {
     Enotik.send_message(2, i, 256 - i);   
   // Serial.println(i);
    delay(50);
  }
 

}
