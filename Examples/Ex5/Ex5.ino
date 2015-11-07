// Подключаем нужные библиотеки
#include <PCF8574.h>
#include "Wire.h"

// Подключаем API Robtech
#include <Robtech.h>

// Объявляем переменную Robot, как экземпляр класса Robtech
Robtech Robot;

// длина стороны периметра
uint8_t _per_side_len;

void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0);
  Robot.printString("Ex #5: Defender", 0, 1);
  // Задаем участок патрулирования
  _per_side_len = 30;
}

void loop() {

  accurateMoveForward(_per_side_len);
  delay(100);// Задержка в 1/10 секунды
  Robot.turnRight(90);
  delay(100);

}

//точное перемещение вперед
void accurateMoveForward(uint8_t dist) {
  Robot.moveForward(AR_MAX_SPEED * 0.5, (int)(dist * 0.25));//25% дистанции разгоняемся
  Robot.moveForward(AR_MAX_SPEED  * 0.7, (int)(dist * 0.5));
  Robot.moveForward(AR_MAX_SPEED * 0.4, (int)(dist * 0.25));//последние 25% дистанции останавливаемся
}
