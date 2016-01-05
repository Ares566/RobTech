#include <PCF8574.h>
#include "Wire.h"
#include <Robtech.h>

Robtech Robot;
#define LEFT_BUMPER_PIN 9
#define RIGHT_BUMPER_PIN 10
#define SPEED 180

// состояния датчиков левого и правого бортов
uint8_t _lb_state = 0, _rb_state = 0;

void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0);
  Robot.printString("Ex #8: Taktil", 0, 1);
  
  // включение подтягивающих резисторов к +5в
  Robot.digitalWriteP(LEFT_BUMPER_PIN, HIGH);
  Robot.digitalWriteP(RIGHT_BUMPER_PIN, HIGH);

  delay(500);
}

void loop() {
  // считываем состояние датчиков
  // 0 - нет столкновения, 1 - сработал датчик
  _lb_state = Robot.digitalReadP(LEFT_BUMPER_PIN);
  _rb_state = Robot.digitalReadP(RIGHT_BUMPER_PIN);
  
  // если нет срабатываний датчиков
  if (!(_lb_state || _rb_state)) {
    Robot.moveForward(SPEED, 0); // едем вперед
  } else { // если произошло столкновение
    Robot.stopMoving();// сначала останавливаемся
    Robot.moveBackward(SPEED, 10); // отъезжаем назад
  
    if (_lb_state) { // совершаем маневр уклонения
      Robot.turnLeft(-30);
    } else {
      Robot.turnRight(-30);
    }
    
  }

  // Задержка в 1/10 секунды
  delay(100);

}


