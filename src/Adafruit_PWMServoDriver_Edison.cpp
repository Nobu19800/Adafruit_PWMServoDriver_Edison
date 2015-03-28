#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "Adafruit_PWMServoDriver_Edison.h"

Adafruit_PWMServoDriver_Edison::Adafruit_PWMServoDriver_Edison(mraa::I2c *i2c, uint8_t addr) {
	_i2c = i2c;
	_i2caddr = addr;
	
}

Adafruit_PWMServoDriver_Edison::~Adafruit_PWMServoDriver_Edison() {
	
}

void Adafruit_PWMServoDriver_Edison::begin(void) {
	
	
	reset();
}

void Adafruit_PWMServoDriver_Edison::reset(void) {
	write8(PCA9685_MODE1, 0x0);
}


void Adafruit_PWMServoDriver_Edison::setPWMFreq(float freq) {
  
  freq *= 0.9;
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;

  uint8_t prescale = floor(prescaleval + 0.5);
  
  
  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10;

  
  write8(PCA9685_MODE1, newmode);
  write8(PCA9685_PRESCALE, prescale);
  write8(PCA9685_MODE1, oldmode);
  usleep(5000);
  write8(PCA9685_MODE1, oldmode | 0xa1);
}

void Adafruit_PWMServoDriver_Edison::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  
 	uint8_t data[5];
	data[0] = LED0_ON_L+4*num;
	data[1] = on;
	data[2] = on>>8;
	data[3] = off;
	data[4] = off>>8;
	_i2c->address(_i2caddr);
	_i2c->write(data,5);
  
}


void Adafruit_PWMServoDriver_Edison::setPin(uint8_t num, uint16_t val, bool invert)
{
  
  val = (uint8_t)std::min((int)val, 4095);
  if (invert) {
    if (val == 0) {
      
      setPWM(num, 4096, 0);
    }
    else if (val == 4095) {
      
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, 4095-val);
    }
  }
  else {
    if (val == 4095) {
      
      setPWM(num, 4096, 0);
    }
    else if (val == 0) {
      
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, val);
    }
  }
}

uint8_t Adafruit_PWMServoDriver_Edison::read8(uint8_t addr) {
	_i2c->address(_i2caddr);
	
	_i2c->writeByte(addr);
	
	

  	return _i2c->readByte();
}

void Adafruit_PWMServoDriver_Edison::write8(uint8_t addr, uint8_t d) {
	_i2c->address(_i2caddr);
	uint8_t data[2];
	data[0] = addr;
	data[1] = d;
	_i2c->write(data,2);
}