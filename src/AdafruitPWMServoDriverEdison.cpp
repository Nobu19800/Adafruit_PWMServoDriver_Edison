// -*- C++ -*-
/*!
 * @file  adafruitpwmservodriveredison.cpp
 * @brief Adafruit PWM ServoDriver Component
 * @date $Date$
 *
 * $Id$
 */

#include "AdafruitPWMServoDriverEdison.h"

#define SERVOMIN  160 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  420 // this is the 'maximum' pulse length count (out of 4096)
#define PI 3.141592

// Module specification
// <rtc-template block="module_spec">
static const char* AdafruitPWMServoDriverEdison_spec[] =
  {
    "implementation_id", "AdafruitPWMServoDriverEdison",
    "type_name",         "AdafruitPWMServoDriverEdison",
    "description",       "Adafruit PWM ServoDriver Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TEST",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.I2C_address", "64",
    "conf.default.I2C_channel", "1",
    // Widget
    "conf.__widget__.I2C_address", "spin",
    "conf.__widget__.I2C_channel", "radio",
    // Constraints
    "conf.__constraints__.I2C_address", "0<=x<=255",
    "conf.__constraints__.I2C_channel", "(1,6)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AdafruitPWMServoDriverEdison::AdafruitPWMServoDriverEdison(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in)
    //m_outOut("out", m_out)

    // </rtc-template>
{
	_pwm = NULL;
	_i2c = NULL;
	
}

/*!
 * @brief destructor
 */
AdafruitPWMServoDriverEdison::~AdafruitPWMServoDriverEdison()
{
}



RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  //addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("I2C_address", m_I2C_address, "64");
  bindParameter("I2C_channel", m_I2C_channel, "1");
  
  // </rtc-template>
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onFinalize()
{
	if(_pwm)
	{
		delete _pwm;
	}
	if(_i2c)
	{
		delete _i2c;
	}
  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onShutdown(RTC::UniqueId ec_id)
{
	

  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onActivated(RTC::UniqueId ec_id)
{
	if(_i2c == NULL)
	{
		_i2c = new mraa::I2c(m_I2C_channel);
	}
	if(_pwm == NULL)
	{
		_pwm = new  Adafruit_PWMServoDriver_Edison(_i2c, m_I2C_address);
		
	}
	_pwm->begin();
	_pwm->setPWMFreq(50);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onExecute(RTC::UniqueId ec_id)
{
  if(m_inIn.isNew())
  {
	m_inIn.read();
	
	for(int i=0;i < m_in.data.length();i++)
	{
		uint16_t pulselen = SERVOMIN + (SERVOMAX - SERVOMIN)*m_in.data[i]/PI;
		_pwm->setPWM(i,0,pulselen);
	}
	
  }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AdafruitPWMServoDriverEdisonInit(RTC::Manager* manager)
  {
    coil::Properties profile(AdafruitPWMServoDriverEdison_spec);
    manager->registerFactory(profile,
                             RTC::Create<AdafruitPWMServoDriverEdison>,
                             RTC::Delete<AdafruitPWMServoDriverEdison>);
  }
  
};


