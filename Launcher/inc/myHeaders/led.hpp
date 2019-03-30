/*
 * led.h
 *
 *  Created on: 2019/03/12
 *      Author: User
 */

#ifndef MYHEADERS_LED_HPP_
#define MYHEADERS_LED_HPP_

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

class LED
{
public:
	LED();

	enum class ledColor : uint16_t { Yellow = 0x8000, Orange = 0x0004, Red = 0x0010 };
	enum class state : bool { ON = true, OFF = false };
	void setNewState(ledColor setLedColor, state newState);

	void toggle(ledColor setLedColor);
};



#endif /* MYHEADERS_LED_HPP_ */
