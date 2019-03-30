
/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#define _DEFAULT_SOURCE
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include <motor.hpp>
#include <electric_valve.hpp>
#include <led.hpp>
#include <rotary_encoder.hpp>
#include <uart.hpp>

constexpr int gcc_version = __GNUC__ ;
constexpr int gcc_minorVersion = __GNUC_MINOR__;

void clockInit();

LED led;
EV ev;

int main(void)
{
	clockInit();

	UART uart1(UART::name::uart1);
	rotaryEncoder rotEnc1(rotaryEncoder::encoderName::RotEnc1);

	std::string sendString;

	while(true)
	{
		sendString.clear();
		sendString = std::to_string(rotEnc1.readCount<int>()) + "\n";
		uart1.TransmitData(sendString);

		led.toggle(LED::ledColor::Yellow);
	}
	return 0;
}

void clockInit()
{
	/*
	 * PLLM = 16, PLLN = 168, PLLP = 2, PLLQ = 8
	 * HSI clock is 16MHz. This is constant value.
	 * Expression of System clock is	: HSI x PLLN / (PLLM x PLLP) = 84MHz
	 * Expression of HCLK clock is		: SystemClock / HCLK_prescaler = 84MHz
	 * Expression of PCLK1 clock is		: HCLK / PCLK1_prescaler = 42MHz
	 * Expression of PCLK2 clock is		: HCLK / PCLK2_prescaler = 84MHz
	 */

	RCC_DeInit();

	FLASH_SetLatency(FLASH_Latency_2);

	RCC_HCLKConfig(RCC_SYSCLK_Div1);					// HCLK prescaler is 1.

	RCC_PCLK1Config(RCC_HCLK_Div2);						// PCLK1 prescaler is 2.
	RCC_PCLK2Config(RCC_HCLK_Div1);						// PCLK2 prescaler is 1.

	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI, 16, 168, 2, 8);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	while(RCC_GetSYSCLKSource() != 0x08);
}
