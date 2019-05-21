/*
 * sequence.hpp
 *
 *  Created on: 2019/04/19
 *      Author: User
 */

#ifndef MYHEADERS_SEQUENCE_HPP_
#define MYHEADERS_SEQUENCE_HPP_

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include <interrupt.hpp>
#include <can.hpp>

#include <move_angle.hpp>
#include <launcher.hpp>
#include <electric_valve.hpp>
#include <led.hpp>
#include <board_io.hpp>
#include <uart.hpp>

constexpr uint8_t MainBoardAddress	= 0x00;
constexpr uint8_t OwnAddress		= 0x01;

constexpr uint8_t CmdIncrementSequence = 0x25;

class Sequence
{
public:
	Sequence() : uart_(UART::name::uart1)
	{
		systick::additionCallFunction( [&]{ update(); } );
		uart1_intrrupt::additionCallFunction( [&](const uint8_t data){receiveParams(data);} );
		//CAN_intrrupt::additionCallFunction( [&](const CanRxMsg& receiveData){ orderReceive_(receiveData); } );
	}
	virtual ~Sequence(){}
private:
	MoveAngle moveAngleMechanism_;
	Launcher launcherMechanism_;
	UART uart_;

	enum class sequenceName
	{
		start,

		getShagai,
		waitGettingShagai,

		setThrowingAngle,
		waitSettingThrowingAngle,

		openArm,
		waitOpennningArm,

		throwShagai,
		waitThrowingShagai,

		waitCommand
	};
	enum class receiveOrderFormat : uint8_t
	{
		start = 0x01,
		fallArm = 0x02,
		getShagai = 0x03,
		throwShagai = 0x04
	};
	enum class compliteCmdFormat : uint8_t
	{
		standbyGettingShagai = 0x01,
		gettigShagai = 0x02,
		throwingComplite = 0x03
	};

	static constexpr int32_t ExpandArmAngle = -500000;

	sequenceName nowSequence_ = sequenceName::start;
	receiveOrderFormat receiveCmd_ = receiveOrderFormat::start;

	int32_t setLauncherAngleValue_ = -1000;

	EV eleValve;
	LED<ledColor::Red> emergencyStateLED;

	static constexpr EV::name expendArmValve = EV::name::EV0;
	static constexpr EV::name fallArmValve = EV::name::EV1;
	static constexpr EV::name holdShagaiValve = EV::name::EV2;

	IO_sigPins<ioName::sig4, ioState::input> expandArmSensor;

	virtual void update() final
	{
		sequenceUpdate_();
		moveAngleMechanism_.update();
		launcherMechanism_.update();
	}
	void sequenceUpdate_();
	void sendConpliteCmd_(const compliteCmdFormat sendCmd);

	static constexpr uint8_t startByte_ = 0xAA;
	void receiveParams(const uint8_t data);
};



#endif /* MYHEADERS_SEQUENCE_HPP_ */
