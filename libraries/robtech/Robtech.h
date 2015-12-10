/*
  Robtech.h - Library for Arduino robotic devices.
  Created by Renat Abaidulin, July 22, 2015.
  Ver. 0.7
*/

#ifndef Robtech_h
#define Robtech_h

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#define AR_M_WITH_ENC 1//режим работы с энкодерами 
//#define AR_M_WITH_NRF 2//режим работы с nrf24l01 
#define AR_M_WITH_LCD 4//режим работы с LCD 


#define AR_WHEEL_D 65 //диаметр колеса в мм
#define AR_MAX_SPEED 255 //максимальная скорость




#define OLED_ADDRESS					0x3C
#define OLED_COMMAND_MODE				0x80
#define OLED_DATA_MODE				0x40


// #define SSD1306_LCDWIDTH                  128
// #define SSD1306_LCDHEIGHT                 64

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

// #define SSD1306_SETLOWCOLUMN 0x00
// #define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
// #define SSD1306_COLUMNADDR 0x21
// #define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

// #define SSD1306_EXTERNALVCC 0x1
// #define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
// #define SSD1306_ACTIVATE_SCROLL 0x2F
// #define SSD1306_DEACTIVATE_SCROLL 0x2E
// #define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
// #define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
// #define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
// #define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
// #define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


class Robtech
{
public:
	
	Robtech();

	void initAR(int mode);
	void moveForward(uint8_t speed, uint16_t distance);//едем вперед
	void moveBackward(uint8_t speed, uint16_t distance);//едем назад
	void turnLeft(int degree);//поворот через левое колесо на определенный градус
	void turnRight(int degree);//поворот через правое колесо на определенный градус
	void stopMoving();//останов обоих моторов
	void waitingDistance4LM(uint16_t distance);//ждем пока левый мотор проедет определенную дистанцию
	void waitingDistance4RM(uint16_t distance);//ждем пока правый мотор проедет определенную дистанцию

	void setLeftWheelSpeed(uint8_t speed);//устанавливаем скорость левого мотора
	uint8_t getLeftWheelSpeed();//берем скорость левого мотора
	void setRightWheelSpeed(uint8_t speed);//устанавливаем скорость правого мотора
	uint8_t getRightWheelSpeed();//берем скорость правого мотора

	//публичные функции работы с энкодерами колес
	uint16_t getCoveredDistance();//пройденное расстояние
	void resetCoveredDistance();//сброс пройденного расстояния
	uint16_t getLeftWheelDistance();//пройденное расстояние левого колеса
	uint16_t getRightWheelDistance();//пройденное расстояние правого колеса
	void resetLeftWheelDistance();//обнуление пройденного расстояния левого колеса
	void resetRightWheelDistance();//обнуление пройденного расстояния правого колеса

	

	//работа с портами через I2C расширитель
	//писать в порт
	void digitalWriteP(uint8_t pin, uint8_t val);
	//инвертировать состояние порта
	void toggleP(uint8_t pin);
	void pinModeP(uint8_t pin, uint8_t mode);
	//читать из порта
	uint8_t digitalReadP(uint8_t pin);
	


	//функции для работы с экраном
	void LCDinit();
	void printChar(char c, byte X=255, byte Y=255);
	void printString(const char *String, byte X=255, byte Y=255, byte numChar=255);
	void clearDisplay();
	
	
	

private:
	
	uint16_t _ar_width;
	void sendCommand(byte command);
	void sendData(byte Data);

	void setCursorXY(byte Column, byte Row);
	
	

};

//функции обрабоки прерываний от энкодера колес
void encoderFuncM_L();
void encoderFuncM_R();
#endif
