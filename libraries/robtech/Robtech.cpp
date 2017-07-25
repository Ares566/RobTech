/*
  Robtech.cpp - Library for Arduino robotic devices.
  Created by Renat Abaidulin, July 22, 2015.
*/


#include <Wire.h>
#include "Robtech.h"
#include <avr/pgmspace.h>
#include <PCF8574.h>


#define ENL 6           // ШИМ вывод для управления правым двигателем 0 - стоп, подтянуто на землю
#define ENR 5           // ШИМ вывод для управления левым двигателем  0 - стоп, подтянуто на землю
#define DIRL 7          // Направление вращение левого двигателя 
#define DIRR 4          // Направление вращение правого двигателя 


// This font be freely used without any restriction(It is placed in public domain)
const byte BasicFont[][8] PROGMEM = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
	{0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
	{0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
	{0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
	{0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
	{0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
	{0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
	{0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
	{0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
	{0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
	{0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
	{0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
	{0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
	{0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
	{0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
	{0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
	{0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
	{0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
	{0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
	{0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
	{0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
	{0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
	{0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
	{0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
	{0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
	{0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
	{0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
	{0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
	{0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
	{0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
	{0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
	{0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
	{0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
	{0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
	{0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
	{0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
	{0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
	{0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
	{0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
	{0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
	{0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
	{0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
	{0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
	{0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
	{0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
	{0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
	{0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
	{0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
	{0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
	{0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
	{0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
	{0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
	{0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
	{0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
	{0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
	{0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
	{0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
	{0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
	{0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
	{0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
	{0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
	{0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
	{0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
	{0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
	{0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
	{0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
	{0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
	{0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
	{0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
	{0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
	{0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
	{0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
	{0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
	{0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
	{0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00} 
};


uint16_t lw_enc_counter,rw_enc_counter;
uint8_t lw_speed,rw_speed;//скорость левого и правого моторов

PCF8574 PCF_20(0x20);


Robtech::Robtech(){
	lw_enc_counter = rw_enc_counter = 0;
	

	pinMode(ENL, OUTPUT);
	pinMode(ENR, OUTPUT);
	pinMode(DIRL, OUTPUT);
	pinMode(DIRR, OUTPUT);
	
	
	
}

//инициализация робота
void Robtech::initAR(int mode){
	_ar_width = 150;
	//инициализация дисплея
	if (mode && AR_M_WITH_LCD){
		LCDinit();
		clearDisplay();
	}
	
	//если режим работы с энкодерами
	if (mode && AR_M_WITH_ENC){
		//подключаем энкодеры
		pinMode(2, INPUT);   //2 пин отвечает за 0 прерывание
		digitalWrite(2, HIGH);       // включаем подтягивающий резистор
		
		pinMode(3, INPUT);   //3 пин отвечает за 1 прерывание
		digitalWrite(3, HIGH);       // включаем подтягивающий резистор
		
		attachInterrupt(1, encoderFuncM_L, CHANGE);  // энкодер левого колеса
		attachInterrupt(0, encoderFuncM_R, CHANGE);  // энкодер правого колеса
	}
}


/*
*  Работа с  моторами
*  при передаче ненулевых параметров выход из функции только по истечении dest
*/

//устанавливаем скорость левого мотора
void Robtech::setLeftWheelSpeed(int speed){
	
	speed = constrain(speed, 0, 255);
	lw_speed = speed;
	analogWrite(ENL,lw_speed);
}

//берем скорость левого мотора
uint8_t Robtech::getLeftWheelSpeed(){
	return lw_speed;
}

//устанавливаем скорость правого мотора
void Robtech::setRightWheelSpeed(int speed){
	
	speed = constrain(speed, 0, 255);
	rw_speed = speed;
	analogWrite(ENR,rw_speed);
}

//берем скорость правого мотора
uint8_t Robtech::getRightWheelSpeed(){
	return rw_speed;
}

//Прямолинейное движение вперед
void Robtech::moveForward(uint8_t speed, uint16_t distance, boolean bWithPID){
	
	digitalWrite(DIRL,HIGH);
	digitalWrite(DIRR,HIGH);
	if (speed){
		setRightWheelSpeed(speed);
		setLeftWheelSpeed(speed);
	}
	

	//обработка distance
	if (speed && distance){
		//waitingDistance4RM(distance);
		uint16_t iBegLWDistance = getLeftWheelDistance();
		uint16_t iBegRWDistance = getRightWheelDistance();
		
		uint16_t lastError = 0;
		uint16_t sumError = 0;
		
		uint16_t KP = 2000 ; //position multiplier (gain)
		uint16_t KI = 100; // Intergral multiplier (gain)
		uint16_t KD = 200; // derivative multiplier (gain)
		uint16_t needed_tick = convertCM2Tick(distance);
		uint16_t needed_tick_lw = lw_enc_counter + needed_tick;
		uint16_t needed_tick_rw = rw_enc_counter + needed_tick;
		
		while((iBegLWDistance + distance) > getLeftWheelDistance()){
			
			
			delay(25);
			

			if (bWithPID){/* использовать PID для синхронизации вращения левого и правого двигателя*/

				int16_t error = -1 * ((needed_tick_lw-lw_enc_counter) - (needed_tick_rw-rw_enc_counter));
				
				if (abs(error)<2){
					continue;
				}
				int16_t P = (int16_t) ((KP * ((int16_t)error) + KD * ((int16_t)(error - lastError)) + KI * ((int16_t)sumError))/1000);
       	    	


			    lastError = error;    
			    sumError += error;
		
			    //scale the sum for the integral term
			    if(sumError > 100) {
			      sumError = 100;
			    } else if(sumError < 0){
			      sumError = 0;
			    }
			    
			    uint8_t deltaMotorSpeed = map(abs(P),0,100,0,((int8_t)(speed*0.1))); 
			    deltaMotorSpeed = (uint8_t) (deltaMotorSpeed /2);
			    
			    uint8_t LWSpeed = getLeftWheelSpeed();
				uint8_t RWSpeed = getRightWheelSpeed();
				
			    if ((int16_t)error < 0){//поворачиваем налево
					setLeftWheelSpeed(LWSpeed + deltaMotorSpeed);
					setRightWheelSpeed(RWSpeed - deltaMotorSpeed);
			    }else{
			     	setLeftWheelSpeed(LWSpeed - deltaMotorSpeed);
					setRightWheelSpeed(RWSpeed + deltaMotorSpeed);
			    }

			}

			
		}
		stopMoving();
	}
}

//едем назад
void Robtech::moveBackward(uint8_t speed, uint16_t distance){

	digitalWrite(DIRL,LOW);
	digitalWrite(DIRR,LOW);
	if (speed){
		setRightWheelSpeed(speed);
		setLeftWheelSpeed(speed);
	}

	//обработка distance
	if (distance){
		waitingDistance4RM(distance);
		

		stopMoving();
	}
}

//поворот через левое колесо на определенный градус
void Robtech::turnLeft(int degree){

	if (degree < 5){
		return;
	}
	
	//поворачиваем вперед...
	if (degree>0){
		digitalWrite(DIRR,HIGH);
	}else
		digitalWrite(DIRR,LOW);//...или назад
	
	//скорость разворота
	uint8_t speed = 200;
	//длина дуги
	uint16_t ArcLen = abs(round(PI * _ar_width * degree / 1800));
	
	//если развернуться нужно на мешьше оборота колеса, делаем скорость ниже
	if (ArcLen < 10){
		speed = 150;
	}
	setLeftWheelSpeed(0);
	setRightWheelSpeed(speed);
	// analogWrite(ENL,0);//левое колесо на месте
	// analogWrite(ENR,speed);//правое крутим
	
	waitingDistance4RM(ArcLen,(ArcLen > 10));
	stopMoving();
}

//поворот через правое колесо на определенный градус
void Robtech::turnRight(int degree){
	
	if (degree < 5){
		return;
	}

	//поворачиваем вперед...
	if (degree>0){
		digitalWrite(DIRL,HIGH);	
	}else
		digitalWrite(DIRL,LOW);//...или назад

	//скорость разворота
	uint8_t speed = 150;
	//длина дуги
	uint16_t ArcLen = abs(round(PI * _ar_width * degree / 1800));

	//если развернуться нужно меньше оборота колеса, делаем скорость ниже
	if (ArcLen < 10){
		speed = 100;
	}
	setLeftWheelSpeed(speed);
	setRightWheelSpeed(0);

	// analogWrite(ENL,speed);
	// analogWrite(ENR,0);

	waitingDistance4LM(ArcLen, (ArcLen > 10));
	stopMoving();
}

//останов обоих моторов
void Robtech::stopMoving(){
	digitalWrite(ENR,0);
	digitalWrite(ENL,0);
}

//ждем пока левый мотор проедет определенную дистанцию
void Robtech::waitingDistance4LM(uint16_t distance, boolean bWithPID){
	uint16_t iCurDistance = getLeftWheelDistance();
	
	uint16_t lastError = 0;
	uint16_t sumError = 0;
	
	uint16_t KP = 3000 ; //position multiplier (gain)
	uint16_t KI = 300; // Intergral multiplier (gain)
	uint16_t KD = 500; // derivative multiplier (gain)
	uint16_t needed_tick = convertCM2Tick(distance);
	uint16_t needed_tick_lw = lw_enc_counter + needed_tick;
	

	while((iCurDistance + distance) > getLeftWheelDistance()){
			
			
			delay(25);
			

			if (bWithPID){/* использовать PID для синхронизации вращения левого и правого двигателя*/
				
				int16_t error = needed_tick_lw - lw_enc_counter;
				 
				if (abs(error)<2){
					continue;
				}
				int16_t P = (int16_t) ((KP * ((int16_t)error) + KD * ((int16_t)(error - lastError)) + KI * ((int16_t)sumError))/1000);
       	    	
			    lastError = error;    
			    sumError += error;
		
			    uint8_t LWSpeed = 100 * 0.2;
			    int8_t deltaMotorSpeed = map( abs(P), 0, 100, -LWSpeed, LWSpeed ); 
			    	    
				setLeftWheelSpeed(100 + deltaMotorSpeed);

			}

			
		}
		
}

//ждем пока правый мотор проедет определенную дистанцию
void Robtech::waitingDistance4RM(uint16_t distance, boolean bWithPID){
	uint16_t iCurDistance = getRightWheelDistance();
	

	uint16_t lastError = 0;
	uint16_t sumError = 0;
	
	uint16_t KP = 3000 ; //position multiplier (gain)
	uint16_t KI = 300; // Intergral multiplier (gain)
	uint16_t KD = 500; // derivative multiplier (gain)
	uint16_t needed_tick = convertCM2Tick(distance);
	uint16_t needed_tick_rw = rw_enc_counter + needed_tick;
	

	while((iCurDistance + distance) > getRightWheelDistance()){
			
			
			delay(25);
			
			

			if (bWithPID){/* использовать PID для синхронизации вращения левого и правого двигателя*/
				
				int16_t error = needed_tick_rw - rw_enc_counter;
				 
				if (abs(error)<2){
					continue;
				}
				int16_t P = (int16_t) ((KP * ((int16_t)error) + KD * ((int16_t)(error - lastError)) + KI * ((int16_t)sumError))/1000);
       	    	
			    lastError = error;    
			    sumError += error;
		
			    uint8_t RWSpeed = 100 * 0.2;
			    int8_t deltaMotorSpeed = map( abs(P), 0, 100, -RWSpeed, RWSpeed ); 
			    	    
				setRightWheelSpeed(100 + deltaMotorSpeed);

			}

			
		}
}

/*
*  Работа с энкодерами моторов
*  подсчитываем пройденное расстояние
*/
//функция вызываемая прерыванием для подсчета оборотов левого колеса


void  encoderFuncM_L() {
	static unsigned long last_interrupt_time_l = 0;
 	unsigned long interrupt_time_l = millis();

  if (digitalRead(3) == HIGH && interrupt_time_l - last_interrupt_time_l > 25) {
    lw_enc_counter++;
    last_interrupt_time_l = interrupt_time_l;
  } 
}
//функция вызываемая прерыванием для подсчета оборотов левого колеса

void encoderFuncM_R() {
	static unsigned long last_interrupt_time_r = 0;
 	unsigned long interrupt_time_r = millis();
 	

	if (digitalRead(2) == HIGH && interrupt_time_r - last_interrupt_time_r > 25) {
		rw_enc_counter++;
		last_interrupt_time_r = interrupt_time_r;
	} 
	
}
//сколько сантиметров проехал робот
uint16_t Robtech::getCoveredDistance(){
	uint16_t _cd = (int)((getLeftWheelDistance() + getRightWheelDistance()) / 2);
	return _cd;
}
//сброс пройденного расстояния
void Robtech::resetCoveredDistance(){
	resetLeftWheelDistance();
	resetRightWheelDistance();
}

uint16_t Robtech::convertCM2Tick(uint16_t cm){
	return round(cm * 200 / (PI*AR_WHEEL_D));
}


//сколько сантиметров проехало левое колесо
uint16_t Robtech::getLeftWheelDistance(){
	
	//один оборот двигателя равен 20 импульсам диаметр колеса в мм
	return round( lw_enc_counter * PI*AR_WHEEL_D / 200 );
}

//сколько сантиметров проехало правое колесо
uint16_t Robtech::getRightWheelDistance(){
	//один оборот двигателя равен 20 импульсам диаметр колеса в мм
	return round( rw_enc_counter * PI*AR_WHEEL_D / 200 );
}

//обнуление пройденного расстояния левого колеса
void Robtech::resetLeftWheelDistance(){
	lw_enc_counter = 0;
}

//обнуление пройденного расстояния правого колеса
void Robtech::resetRightWheelDistance(){
	rw_enc_counter = 0;
}

void Robtech::digitalWriteP(uint8_t pin, uint8_t val){
	if (pin<1)
	{
		return;
	}
	if (pin>8)
	{
		/* стандартный digitalWrite */
		digitalWrite(pin,val);
	}else
		PCF_20.write(pin-1, val);
}

void Robtech::toggleP(uint8_t pin){
	return PCF_20.toggle(pin);
}
void Robtech::pinModeP(uint8_t pin, uint8_t mode){
	if (pin<1)
	{
		return;
	}
	if (pin>8)
	{
		/* стандартный digitalRead */
		pinMode(pin,mode);
	}
}
uint8_t Robtech::digitalReadP(uint8_t pin){
	if (pin<1)
	{
		return 0;
	}
	if (pin>8)
	{
		/* стандартный digitalRead */
		return digitalRead(pin);
	}
	return PCF_20.read(pin-1);
}


//wire interface to OLED
void Robtech::sendCommand(byte command){
	Wire.beginTransmission(OLED_ADDRESS); // begin transmitting
	Wire.write(OLED_COMMAND_MODE);//data mode
	Wire.write(command);
	Wire.endTransmission();    // stop transmitting
}


void Robtech::sendData(byte data){
	
	Wire.beginTransmission(OLED_ADDRESS); // begin transmitting
	Wire.write(OLED_DATA_MODE);//data mode
	Wire.write(data);
	Wire.endTransmission();    // stop transmitting

}

void Robtech::printChar(char C, byte X, byte Y){

	if ( X < 128 )
		setCursorXY(X, Y);

	//Ignore unused ASCII characters. Modified the range to support multilingual characters.
    if(C < 32 || C > 127)
		C='*'; //star - indicate characters that can't be displayed

	
    for(byte i=0; i<8; i++) {
	
       //read bytes from code memory
       sendData(pgm_read_byte(&BasicFont[C-32][i])); //font array starts at 0, ASCII starts at 32. Hence the translation
	 
    }
}

void Robtech::printString(const char *String, byte X, byte Y, byte numChar){

	if ( X < 128 )
		setCursorXY(X, Y);

	
	byte count=0;
    while(String[count] && count<numChar){
		printChar(String[count++]);  
	}

}

void Robtech::LCDinit(){
	Wire.begin();
	
	byte twbrbackup = TWBR;
	TWBR = 12; 
	
// Init sequence for 128x64 OLED module
    sendCommand(SSD1306_DISPLAYOFF);                    // 0xAE
    sendCommand(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    sendCommand(0x80);                                  // the suggested ratio 0x80
    sendCommand(SSD1306_SETMULTIPLEX);                  // 0xA8
    sendCommand(0x3F);
    sendCommand(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    sendCommand(0x0);                                   // no offset
    sendCommand(SSD1306_SETSTARTLINE | 0x0);            // line #0
    sendCommand(SSD1306_CHARGEPUMP);                    // 0x8D
    sendCommand(0x14); 
    sendCommand(SSD1306_MEMORYMODE);                    // 0x20
    sendCommand(0x00);                                  // 0x0 act like ks0108
    sendCommand(SSD1306_SEGREMAP | 0x1);
    sendCommand(SSD1306_COMSCANDEC);
    sendCommand(SSD1306_SETCOMPINS);                    // 0xDA
    sendCommand(0x12);
    sendCommand(SSD1306_SETCONTRAST);                   // 0x81
    sendCommand(0xCF); 
    sendCommand(SSD1306_SETPRECHARGE);                  // 0xd9
    sendCommand(0xF1);
    sendCommand(SSD1306_SETVCOMDETECT);                 // 0xDB
    sendCommand(0x40);
    sendCommand(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    sendCommand(SSD1306_NORMALDISPLAY);                 // 0xA6
    sendCommand(SSD1306_DISPLAYON);
}

void Robtech::setCursorXY(byte X, byte Y){
	
    sendCommand(0x00 + (8*X & 0x0F)); 		//set column lower address
    sendCommand(0x10 + ((8*X>>4)&0x0F)); 	//set column higher address
	sendCommand(0xB0 + Y); 					//set page address	
}


void Robtech::clearDisplay()	{

	for(byte page=0; page<8; page++) {	
		setCursorXY(0, page);     
		for(byte column=0; column<128; column++){  //clear all columns
			sendData(0);    
		}
	}
	setCursorXY(0,0);  
	
}
