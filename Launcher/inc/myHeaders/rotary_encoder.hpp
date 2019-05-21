/*
 * rotary_encoder.h
 *
 *  Created on: 2019/03/01
 *      Author: User
 */

#ifndef MYHEADERS_ROTARY_ENCODER_HPP_
#define MYHEADERS_ROTARY_ENCODER_HPP_

#include <type_traits>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

enum class encoderName : uint8_t {RotEnc1, RotEnc2};

class RotaryEncoder
{
private:
	const encoderName useRotEncName_;

public:
	TIM_TypeDef* const useTimer_;
	RotaryEncoder() = delete;

	RotaryEncoder(const encoderName useRotEnc)
				: useRotEncName_(useRotEnc), useTimer_(getUseTimer_(useRotEnc))
	{
		timerClockInit_();
		configEncoderInterfaceMode_();
		configEncoderPins_();
	}
	RotaryEncoder(const encoderName useRotEnc, const uint32_t setPeriod)
				: useRotEncName_(useRotEnc), useTimer_(getUseTimer_(useRotEnc))
	{
		timerClockInit_();
		configEncoderInterfaceMode_(setPeriod);
		configEncoderPins_();
	}

	template<typename T>
	std::enable_if_t<std::is_unsigned<T>::value, T> readCount() const
	{
		return (T)useTimer_->CNT;
	}

	template<typename T>
	std::enable_if_t<std::is_signed_v<T> && !std::is_floating_point_v<T>, T> readCount() const
	{
		const uint32_t countValue = (uint32_t)useTimer_->CNT;
		std::make_unsigned_t<T> returnValue = 0;
	    if(countValue > ((uint32_t)(useTimer_->ARR/2)))
		{
	    	/*Complement representation*/
			returnValue = returnValue - 1;	//returnValue is 0x~FFFF.
			returnValue = returnValue - (std::make_unsigned_t<T>)useTimer_->ARR;
			returnValue = returnValue + (std::make_unsigned_t<T>)countValue;
		}
		else
		{
			returnValue = (std::make_unsigned_t<T>)countValue;
		}
		return (T)returnValue;
	}

	template<typename T>
	inline std::enable_if_t<std::is_floating_point<T>::value, T> readCount() const
		{ return (double)readCount<int32_t>(); }

	inline void clearCount(){ useTimer_->CNT = 0; }
	inline void setCount(uint32_t setValue){ useTimer_->CNT = setValue; }


	virtual ~RotaryEncoder(){}

protected:
	inline void timerClockInit_()
	{
		const uint32_t RCC_Periph = (useRotEncName_ == encoderName::RotEnc1 ? RCC_APB1Periph_TIM3 : RCC_APB1Periph_TIM2);
		RCC_APB1PeriphClockCmd(RCC_Periph, ENABLE);
	}

	void configEncoderInterfaceMode_();
	inline void configEncoderInterfaceMode_(const uint32_t setPeriod)
	{
		configEncoderInterfaceMode_();
		TIM_SetAutoreload(useTimer_, setPeriod);
	}

	void configEncoderPins_timer2_();
	void configEncoderPins_timer3_();
	inline void configEncoderPins_()
	{
		if(useTimer_ == TIM2)configEncoderPins_timer2_();
		else configEncoderPins_timer3_();
	}
	TIM_TypeDef* getUseTimer_(encoderName useRotEnc)
	{
		if(encoderName::RotEnc1 == useRotEnc) return TIM3;
		return TIM2;
	}
};



#endif /* MYHEADERS_ROTARY_ENCODER_HPP_ */
