#include <PCF8574.h>
#include "Wire.h"
#include <Robtech.h>
#include <Servo.h> // библиотека управления сервоприводами
#include <NewPing.h>

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 400
//Ultrasonic ultrasonic(TRIG, ECHO);
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define S_RIGHT 0
#define S_FRONT 90
#define S_LEFT 180
Robtech Robot;
Servo servoSensor;// сервопривод сонара
// Задаем расстояние см
uint8_t _dist2obstacle = 20;
uint8_t _speed = 100;
uint8_t _curSonarDir = 200;
void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0);
  Robot.printString("Ex #7: Labyrinth", 0, 1);
  // инициализация сервопривода
  servoSensor.attach(11);
  delay(500);
}

char buf[40];
uint16_t coveredDistance = 0;
void loop() {
  // сбрасываем пройденное расстояние
  Robot.resetCoveredDistance();
  // проверяем пространство перед роботом
  uint8_t dist2front = getDistance4(S_FRONT);
  if (dist2front < _dist2obstacle * 2) {
    Robot.stopMoving();
    delay(300);
    Robot.turnLeft(90);
    dist2front = getDistance4(S_FRONT);
  }
  sprintf(buf, "dist2front = %d", dist2front);
  Robot.printString(buf, 0, 4);
    
  while (Robot.getCoveredDistance() < dist2front - _dist2obstacle * 2) {
    /* модуль движения вдоль стены */
    // узнаем дистанцию до стены справа
    uint8_t dist2s = getDistance4(S_RIGHT);

    sprintf(buf, "dist2s = %d", dist2s);
    Robot.printString(buf, 0, 5);
  
    // вычисляем ошибку между ожидаемым и реальным
    // расстояниями до стены
    int8_t dist_error = dist2s - _dist2obstacle;
    // применяем пропорциональный регулятор
    int8_t kSpeed = dist_error / 2;
    // к скорости колес
    int16_t newLWS =  _speed + kSpeed;
    int16_t newRWS =  _speed - kSpeed;
    newLWS = constrain(newLWS, 110, 255);
    newRWS = constrain(newRWS, 110, 255);
    Robot.setLeftWheelSpeed(newLWS);
    Robot.setRightWheelSpeed(newRWS);
    if(_speed < 180)
      _speed += 2;
    // едем вперед с вычисленными скоростями
    Robot.moveForward(0, 0);
  }

  Robot.setLeftWheelSpeed(150);
  Robot.setRightWheelSpeed(150);

  
}

// взять расстояние до стены с определенной стороны
uint16_t getDistance4(uint8_t side) {
  if (_curSonarDir != side) {
    servoSensor.write(side);
    _curSonarDir = side;
    delay(300);
  }
  return ultrasonic.ping_cm();
}


