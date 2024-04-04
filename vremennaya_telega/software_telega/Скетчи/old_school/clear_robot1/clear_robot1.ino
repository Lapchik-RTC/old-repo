#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "motor.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"
//////////////

void Drive_Normal(byte, byte);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Enotik.init_slave(0x01);
  Enotik.bind(2, Drive_Normal);

 // motor1.init(DELTA_SOFT_SPEED_PWM , DELTA_SOFT_TIME_MS, MAX_MOTOR_CURRENT_MA, CURRENT_KP);
 // motor2.init(DELTA_SOFT_SPEED_PWM , DELTA_SOFT_TIME_MS, MAX_MOTOR_CURRENT_MA, CURRENT_KP);
}

void loop() {
  Enotik.work();
}

void Drive_Normal(byte v1, byte v2)
{
  
  int v1_1 = (int) v1;
  int v2_1 = (int) v2;
  Serial.println(v1_1);
}
