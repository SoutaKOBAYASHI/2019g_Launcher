/*
 * move_angle.cpp
 *
 *  Created on: 2019/04/06
 *      Author: User
 */
#include <move_angle.hpp>


void MoveAngle::switchControl_()
{
	PositionPID::SetSpeed(getZeroPointSpeed, MotorDriver::MotorDriveMode::PID);
}
void MoveAngle::zeroPointIntrrupt_()
{
	if(isGotZeroPoint_)return;
	PositionPID::SetSpeed(0, MotorDriver::MotorDriveMode::DutyControl);
	PositionPID::setPositionCount((int32_t)movePositions::downPosition);
	isGotZeroPoint_ = true;
}
void MoveAngle::moveAngle_Update()
{
	if(!upSig.readNowState() || !downSig.readNowState())
	{
		switchControl_();
		PositionPID::setEnableState(false);
	}
	else
	{


		if(!isGotZeroPoint_)
		{
			getZeroPoint_();
		}

		if(emergencySwitch.readNowState() && isGotZeroPoint_)
		{
			PositionPID::setEnableState(true);
		}
		else
		{
			PositionPID::setEnableState(false);
		}
	}
}



