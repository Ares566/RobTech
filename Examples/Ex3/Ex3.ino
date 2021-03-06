// Подключаем API Robtech
#include <Robtech.h>

// Объявляем переменную Robot, как экземпляр класса Robtech
Robtech Robot;

// здесь мы запускаем инициализации, эта функция вызовется только единожды при включении платформы
void setup() {
  Robot.initAR(AR_M_WITH_ENC && AR_M_WITH_LCD);
  Robot.printString("RobTech", 5, 0); // Печатаем на LCD строку
  Robot.printString("Ex #3: Harvester", 0, 1);
}

// Счетчик итераций
uint8_t iIterCNT = 0;

// Буфер для отображения текстовой информации на LCD экране
char buf[100];

void loop() {

  if (iIterCNT < 3) { // выполняем 3 раза

    // обнуляем пройденное расстояние правого колеса
    Robot.resetRightWheelDistance();
    // вызываем функцию "точного" перемещения вперед
    accurateMoveForward();

    // берем пройденное расстояние правого колеса
    uint16_t iDistance = Robot.getRightWheelDistance();
    // заполняем буфер нужными данными
    sprintf(buf, "Dist = %d", iDistance);
    // выводим буфер на экран с начала третьей строки
    Robot.printString(buf, 0, 3);

    // ждем полсекунды
    delay(500);
    //...и назад
    accurateMoveBackward();

    // увеличиваем счетчик итераций
    iIterCNT++;
    // ждем полсекунды до следующей итерации
    delay(500);
  }

}

//точное перемещение вперед
void accurateMoveBackward() {
  //параметры нужно подставить
  //из лучшего результата предыдущего эксперимента
  Robot.moveForward(AR_MAX_SPEED * 0.7, 7);
  Robot.moveForward(AR_MAX_SPEED * 0.8, 8);
  Robot.moveForward(AR_MAX_SPEED * 0.6, 15);
}

//точное перемещение назад
void accurateMoveForward() {
  //параметры нужно подставить
  //из лучшего результата предыдущего эксперимента
  Robot.moveBackward(AR_MAX_SPEED * 0.7, 7);
  Robot.moveBackward(AR_MAX_SPEED * 0.8, 8);
  Robot.moveBackward(AR_MAX_SPEED * 0.6, 15);
}
