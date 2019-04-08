#include <rotary_encoder.hpp>

void RotaryEncoder::configEncoderInterfaceMode_()
{
	TIM_EncoderInterfaceConfig(useTimer_, TIM_EncoderMode_TI12 , TIM_ICPolarity_Rising , TIM_ICPolarity_Rising);
	TIM_Cmd(useTimer_ , ENABLE);

	TIM_SetAutoreload(useTimer_, (uint32_t)UINT16_MAX);

	TIM_SetCounter(useTimer_, 0);
}

void RotaryEncoder::configEncoderPins_timer2_()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Pin		= GPIO_Pin_0 | GPIO_Pin_1;
	gpioInitStruct.GPIO_Mode	= GPIO_Mode_AF;
	gpioInitStruct.GPIO_PuPd	= GPIO_PuPd_UP;
	gpioInitStruct.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
}

void RotaryEncoder::configEncoderPins_timer3_()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Pin		= GPIO_Pin_6;
	gpioInitStruct.GPIO_Mode	= GPIO_Mode_AF;
	gpioInitStruct.GPIO_PuPd	= GPIO_PuPd_UP;
	gpioInitStruct.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);

	gpioInitStruct.GPIO_Pin		= GPIO_Pin_5;
	GPIO_Init(GPIOB, &gpioInitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);
}
