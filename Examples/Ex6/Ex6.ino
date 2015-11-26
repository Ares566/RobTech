#include <PCF8574.h>
#include "Wire.h"
#include <NewPing.h>
#include <Robtech.h>

#define TRIG 9
#define ECHO 10
#define MAX_DISTANCE 400
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

Robtech Robot;

uint8_t _dist2front;

void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0);
  Robot.printString("Ex #6: ACC", 0, 1);
  // Задаем расстояние см
  _dist2front = 10;
  delay(500);
}


void loop() {
  // взять отфильтрованные данные о дальности препятствия
  uint16_t _d2o = ultrasonic.RangClear();
  // если робот в "опасной" зоне - остановиться
  if (_d2o < _dist2front){
    Robot.stopMoving();
  }else if(_d2o > 40){
    Robot.moveForward(AR_MAX_SPEED, 0);
  }else{
    // иначе вычисляем скорость для плавного старта остановки
    uint8_t _speed = map(abs(_d2o - _dist2front), 5, 40, 150, AR_MAX_SPEED);
    Robot.moveForward(_speed, 0);
  }
  delay(100);

}

