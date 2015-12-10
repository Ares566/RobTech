#include <PCF8574.h>
#include "Wire.h"
#include <Robtech.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 400

NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Robtech Robot;
Servo servoSensor;

#define MIDDLE_IR_PIN 1

void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0);
  Robot.printString("Ex#10: Kegelring", 0, 1);
  Robot.pinModeP(MIDDLE_IR_PIN, INPUT);
  servoSensor.attach(11);
  servoSensor.write(90);
  delay(500);
}

char buf[40];
uint8_t iNumOfPins = 12;
uint8_t iNumCleared = 0;
void loop() {
  // работаем пока не удалим все кегли
  if(iNumCleared >= iNumOfPins){
      return;
  }

  uint16_t minD = 10000;
  int minDAngle = 200;

  // осматриваем переднюю полусферу
  for(uint8_t iAngle=0; iAngle<180; iAngle+=5){
      servoSensor.write(iAngle);
      delay(200);
      
      // находим ближайшую кеглю
      uint16_t curD = ultrasonic.ping_cm();
      if(curD < minD){
        minD = curD;
        minDAngle = iAngle;// запоминаем угол до ближайшей кегли
      }
  }
  // Выводим отладочную информацию
  sprintf(buf, "minDAngle = %d", minDAngle);
  Robot.printString(buf, 0, 4);
  // Для наглядности поворачиваем сонар в сторону кегли
  servoSensor.write(minDAngle);
  delay(500);

  // переводим в угловые координаты робота
  minDAngle -= 90;
  // совершаем разворот в сторону кегли
  Robot.turnLeft( minDAngle / 2);
  Robot.turnRight( -minDAngle / 2);  
  Robot.stopMoving();

  // сбрасываем пройденное расстояние
  Robot.resetCoveredDistance();
  
  // едем пока не пересечем линию
  while (Robot.digitalReadP(MIDDLE_IR_PIN) != 0){//0 если над линией
    Robot.moveForward(180, 0);
  }
  Robot.stopMoving();
  // берем пройденное расстояние
  uint16_t iCoveredD = Robot.getCoveredDistance();
  // сбрасываем пройденное расстояние
  Robot.resetCoveredDistance();
  // едем на эту дистанцию назад, в центр контура
  Robot.moveBackward(180, iCoveredD);
  
  // повторяем алгоритм
  iNumCleared++;
}

