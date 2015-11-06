// Подключаем нужные библиотеки
#include <PCF8574.h>
#include "Wire.h"

// Подключаем API Robtech
#include <Robtech.h>

// Объявляем переменную Robot, как экземпляр класса Robtech
Robtech Robot;

// Переменные, которые нам потребуются для решения нашей задачи
uint8_t _rw_speed, _lw_speed;
// В отличие от скорости, радиус и коэффициент числа с плавающей точкой
float radius, koef;

// Буфер для отображения текстовой информации на LCD экране
char buf[100];

void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  // Печатаем на LCD
  Robot.printString("RobTech", 5, 0);
  Robot.printString("Ex #4: Circus", 0, 1);

  // Задаем константы
  _rw_speed = round(AR_MAX_SPEED * 0.8);
  radius = 30.0;

  // Вычисляем коэффициент
  koef = radius / (radius - 13);
  // Уменьшаем скорость левого колеса на коэффициент k
  _lw_speed = (int)(_rw_speed / koef);
}

// "Бесконечный цирк"
void loop() {

  /* включаем движение вперед
   * так как скорость установлена в 0
   * робот стоит и не двигается
  */
  Robot.moveForward(0, 0);

  // Устанавливаем скорости колес
  Robot.setRightWheelSpeed(_rw_speed);
  Robot.setLeftWheelSpeed(_lw_speed);
  // и робот начинает движение

  // Выводим отладочную информацию - скорости колес
  sprintf(buf, "LW = %d, RW = %d", _lw_speed, _rw_speed);
  Robot.printString(buf, 0, 3);

  // Задержка в 1/10 секунды
  delay(100);

}

