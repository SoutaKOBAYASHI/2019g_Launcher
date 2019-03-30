/*
 * led.cpp
 *
 *  Created on: 2019/03/12
 *      Author: User
 */
#include <led.hpp>

LED::LED()
{
	/*Enable to supply clock for GPIOs.*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);


	/*Configuration GPIO pins.*/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_2 | GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void LED::setNewState(ledColor setLedColor, state newState)
{
	GPIO_TypeDef* setGPIO =
			setLedColor == ledColor::Yellow ? GPIOA : GPIOB;

	if(newState == state::ON)GPIO_SetBits(setGPIO, (uint16_t)setLedColor);
	else GPIO_ResetBits(setGPIO, (uint16_t)setLedColor);
}

void LED::toggle(ledColor setLedColor)
{
	GPIO_TypeDef* setGPIO =
				setLedColor == ledColor::Yellow ? GPIOA : GPIOB;

	if(!GPIO_ReadOutputDataBit(setGPIO, (uint16_t)setLedColor))GPIO_SetBits(setGPIO, (uint16_t)setLedColor);
	else GPIO_ResetBits(setGPIO, (uint16_t)setLedColor);
}
