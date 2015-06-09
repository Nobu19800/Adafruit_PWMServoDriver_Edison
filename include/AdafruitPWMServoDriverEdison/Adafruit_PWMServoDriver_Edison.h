#ifndef Adafruit_PWMServoDriver_Edison_H
#define Adafruit_PWMServoDriver_Edison_H

#include <stdio.h>
#include <mraa.hpp>

#include "i2c_smf.h"


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

class Adafruit_PWMServoDriver_Edison
{
public:
	Adafruit_PWMServoDriver_Edison(mraa::I2c *i2c, uint8_t addr = 0x40);
	~Adafruit_PWMServoDriver_Edison();
	void begin(void);
	void reset(void);
	void setPWMFreq(float freq);
	void setPWM(uint8_t num, uint16_t on, uint16_t off);
	void setPin(uint8_t num, uint16_t val, bool invert=false);
	
private:
	uint8_t _i2caddr;
	//int _i2channel;



	mraa::I2c *_i2c;

	i2c_smf *_smf;
};





#endif