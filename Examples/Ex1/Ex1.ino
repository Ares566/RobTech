// Подключаем нужные библиотеки
#include <PCF8574.h>
#include "Wire.h"

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
	if(!finish){// выполняем пока не финишировали
				
		Robot.moveForward(AR_MAX_SPEED,30); // проехать на максимальной скорости 30 см
		
		finish = true; // поднять финишный флаг
	}
}
