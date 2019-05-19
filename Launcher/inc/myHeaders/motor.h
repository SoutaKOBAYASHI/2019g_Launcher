/*
 * motor.h
 *
 *  Created on: 2019/02/23
 *      Author: User
 */

#ifndef MYHEADERS_MOTOR_H_
#define MYHEADERS_MOTOR_H_

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include <cmath>

class motorControl
{
public:
	motorControl();
	motorControl(const uint16_t resolution, const uint32_t frequency);

	enum class driveMode : uint8_t{ SMB, LAP };
	inline void setDriveMode(const driveMode setMode) { nowDriveMode_ = setMode; }
	const driveMode& getNowDriveMode = nowDriveMode_;

	void setSpeed(const int32_t setValue);
	void setSpeed(const int32_t setValue, const driveMode setMode);

	~motorControl();

private:
	driveMode nowDriveMode_ = driveMode::SMB;
	static constexpr uint16_t defaultResolution_	= 100;
	static constexpr uint32_t defaultFrequency_		= 20000;

	uint16_t nowResolution_ = defaultResolution_;

	constexpr uint16_t prescaler_
		(const uint16_t resolution, const uint32_t pwmFreq, const uint32_t timerFrequency);

	void GPIO_PinsInit_();
	void timerInit_(const uint16_t resolution, const uint32_t pwmFreq);
};


#endif /* MYHEADERS_MOTOR_H_ */