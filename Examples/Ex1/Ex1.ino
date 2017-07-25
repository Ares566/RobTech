// Подключаем API Robtech
#include <Robtech.h>

// Объявляем переменную Robot, как экземпляр класса Robtech
Robtech Robot;

// Переменная, указывающая что мы финишировали
boolean finish = false;

// здесь мы запускаем инициализации, эта функция вызовется только единожды при включении платформы
void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0); // Печатаем на LCD строку
}

char buf[40];

// здесь мы пишем основной код логики робота,
// функция loop вызывается заново как только ее работа была закончена
void loop() {
  sprintf(buf, "Distance %d", Robot.getLeftWheelDistance());
  Robot.printString(buf, 0, 3);

  if (!finish) { // выполняем пока не финишировали
    Robot.moveForward(AR_MAX_SPEED, 30); // проехать на максимальной скорости 30 см
    finish = true; // поднять финишный флаг
  }
}
