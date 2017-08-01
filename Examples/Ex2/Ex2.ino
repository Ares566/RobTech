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



// здесь мы пишем основной код логики робота,
// функция loop вызывается заново как только ее работа была закончена
void loop() {
  if (!finish) { // выполняем пока не финишировали

    // старт со скоростью 30% от максимума, 7 см
    Robot.moveForward(AR_MAX_SPEED * 0.7, 7);

    // перемещение со скоростью 100%, 15 см
    Robot.moveForward(AR_MAX_SPEED, 8);

    // сбрасываем скорость до 30%, 8 см затем останов
    Robot.moveForward(AR_MAX_SPEED * 0.3, 15);

    finish = true; // поднять финишный флаг
  }
}
