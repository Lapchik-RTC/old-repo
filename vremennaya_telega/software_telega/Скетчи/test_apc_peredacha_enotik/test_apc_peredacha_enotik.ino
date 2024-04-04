#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"

void setup() {
  Enotik.init_slave(0x01);
  Enotik.bind(7, priem);
  Serial1.begin(9600);
  Serial.begin(9600);
 // Serial1.begin(9600);

}

void loop() 
{
  Enotik.work();
//  for (int i=0; i<256; i++)
//  {
//    Serial1.write(i);
//   // Serial.println(i);
//    delay(50);
//  }

}


void priem(byte n, byte m){
  Serial.print(n);
  Serial.print("  ");
  Serial.println(m);
}

