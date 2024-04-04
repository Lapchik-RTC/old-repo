#include "motor.h"

char symbol;

enum States
{
  WAITING,
  READING,
  RUNNING,
  ERROR
};

States state;
States onWait();
States onRead();
States onRun();
States onError();

//////////////
#define DELTA_SOFT_SPEED_PWM 15
#define DELTA_SOFT_TIME_MS 5
#define MAX_MOTOR_CURRENT_MA 1300
#define CURRENT_KP 0.1


void setup()
{
  motor1.init(DELTA_SOFT_SPEED_PWM , DELTA_SOFT_TIME_MS, MAX_MOTOR_CURRENT_MA, CURRENT_KP);
  motor2.init(DELTA_SOFT_SPEED_PWM , DELTA_SOFT_TIME_MS, MAX_MOTOR_CURRENT_MA, CURRENT_KP);

  Serial1.begin(19200);
}

void loop()
{
  motor1.work();
  motor2.work();
  switch (state)
  {
    case WAITING:
      state = onWait();
      break;
    case READING:
      state = onRead();
      break;
    case RUNNING:
      state = onRun();
      break;
    default:
      state = onError();
  }
}

States onWait()
{
  if (Serial.available() > 0)
  {
    return READING;
  }
  return WAITING;
}

States onRead()
{
  symbol = Serial.read();
  return RUNNING;
}

States onRun()
{
    motor1.work();
  motor2.work();
  switch (symbol)
  {
    case '1':
      motor1.drive(200);
      motor2.drive(200);
      break;
    case '0':
      motor1.brake();
      motor2.brake();
      break;
    case '2':
      motor1.drive(-100);
      motor2.drive(-100);
      break;
    case '3':
      motor1.drive(-200);
      motor2.drive(200);
      break;
    case '4':
      motor1.drive(200);
      motor2.drive(-200);
      break;
    default:
      return ERROR;
  }
  return WAITING;
}

States onError()
{
  //Получены неоговоренные символы. Очищаем ввод и продолжаем.
  //Здесь можно добавить какие-то действия для этой ситуации.
  //...
  while (Serial.available())
  {
    Serial.read();
  }
  return WAITING;
}


