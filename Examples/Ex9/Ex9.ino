#include <PCF8574.h>
#include "Wire.h"
#include <Robtech.h>

Robtech Robot;
#define MIDDLE_IR_PIN 1

void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0);
  Robot.printString("Ex #9: Snowblower", 0, 1);
  Robot.pinModeP(MIDDLE_IR_PIN, INPUT);
  delay(500);
}

//char buf[40];
uint8_t numOfSectors = 12;
uint8_t iCurSector = 0;
void loop() {
  // работаем пока не почистим все секторы
  if(iCurSector >= numOfSectors){
      return;
  }

  
  // сбрасываем пройденное расстояние
  Robot.resetCoveredDistance();
  
  
  // sprintf(buf, "dist2front = %d", dist2front);
  // Robot.printString(buf, 0, 4);
  
  
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
  // поворачиваемся на заданный угол
  Robot.turnLeft(360 / numOfSectors);

  // повторяем алгоритм со следующим сектором
  iCurSector++;
}



