/*
 * sequence.cpp
 *
 *  Created on: 2019/04/19
 *      Author: User
 */

#include <sequence.hpp>

void Sequence::sequenceUpdate_()
{
	static uint16_t waitCount = 0;

	/*This lambda function returns true if it has to wait. */
	auto waiting = [&]	{
							if(waitCount > 0)waitCount--;
							return waitCount == 0 ? false : true;
						};

	if(emergencySwitch.readNowState())
	{
		emergencyStateLED.setNewState(state::ON);
	}
	else
	{
		emergencyStateLED.setNewState(state::OFF);

		//receiveCmd_ = receiveOrderFormat::throwShagai;
		switch(nowSequence_)
		{
		case sequenceName::start :
			moveAngleMechanism_.setTargetMovePosition(moveAngleMechanism_.movePositions::throwingPosition);
			launcherMechanism_.setLauncherSequence(Launcher::launcherSequence::returnZeroPoint);
			eleValve.setNewState(EV::state::Reset, expendArmValve, fallArmValve);
			eleValve.setNewState(EV::state::Set, holdShagaiValve);
			//eleValve.setNewState(EV::state::Set, holdShagaiValve);
			if(receiveCmd_ != receiveOrderFormat::start && launcherMechanism_.isGotZeroPoint && moveAngleMechanism_.isGotZeroPoint)
			{
				nowSequence_ = sequenceName::getShagai;
			}
			break;

		case sequenceName::getShagai:
			eleValve.setNewState(EV::state::Reset, holdShagaiValve);
			waitCount = 1000;
			nowSequence_ = sequenceName::waitGettingShagai;
			break;

		case sequenceName::waitGettingShagai:
			if(!waiting())nowSequence_ = sequenceName::setThrowingAngle;
			break;

		case sequenceName::setThrowingAngle:
			moveAngleMechanism_.setTargetMovePosition_v(setLauncherAngleValue_);
			if(moveAngleMechanism_.isAnglePID_OK())
			{
				waitCount = 200;
				nowSequence_ = sequenceName::waitSettingThrowingAngle;
			}
			break;

		case sequenceName::waitSettingThrowingAngle:
			if(!waiting())
			{
				sendConpliteCmd_(compliteCmdFormat::gettigShagai);
				if(receiveCmd_ == receiveOrderFormat::throwShagai)nowSequence_ = sequenceName::openArm;
			}
			break;

		case sequenceName::openArm:
			eleValve.setNewState(EV::state::Set, holdShagaiValve);
			waitCount = 550;
			nowSequence_ = sequenceName::waitOpennningArm;
			break;

		case sequenceName::waitOpennningArm:
			if(!waiting())
			{
				launcherMechanism_.setLauncherSequence(Launcher::launcherSequence::launch);
				nowSequence_ = sequenceName::throwShagai;
			}
			break;

		case sequenceName::throwShagai:
			if(launcherMechanism_.nowSequence == Launcher::launcherSequence::returnZeroPoint)
			{
				waitCount = 500;
				nowSequence_ = sequenceName::waitThrowingShagai;
			}
			break;

		case sequenceName::waitThrowingShagai:
			if(!waiting())
			{
				//eleValve.setNewState(EV::state::Reset, holdShagaiValve);
				sendConpliteCmd_(compliteCmdFormat::throwingComplite);
				nowSequence_ = sequenceName::waitCommand;
				receiveCmd_ = receiveOrderFormat::start;
			}
			break;

		case sequenceName::waitCommand:
			if(receiveCmd_ != receiveOrderFormat::start)nowSequence_ = sequenceName::waitOpennningArm;
			break;

		}
	}
}
void Sequence::sendConpliteCmd_(const compliteCmdFormat sendCmd)
{
	const std::array<uint8_t, 2> sendData = { OwnAddress, (uint8_t)sendCmd };
	ControlAreaNetwork::sendData(sendData, MainBoardAddress);
}
void Sequence::receiveParams(const uint8_t data)
{
	static uint8_t receiveStartByte = 0;
	static std::array<uint8_t, 8> receiveDataArr = {};
	static uint8_t receiveCheckSum = 0;
	uint8_t checkSum = 0;
	static uint8_t receiveCount = 0;

	int32_t setSpeed = 0;
	int32_t setAngle = 0;

	auto receiveDataCheck = [](const int32_t speed, const int32_t angle)
			{return speed < Launcher::throwingMinSpeed && Launcher::throwingMaxSpeed < speed && angle < (int32_t)MoveAngle::movePositions::downPosition && (int32_t)MoveAngle::movePositions::upPosition < angle;};

	switch(receiveCount)
	{
	case 0:
		receiveStartByte = data;
		break;

	case 9:
		receiveCheckSum = data;
		break;

	default:
		receiveDataArr[receiveCount - 1] = data;
		break;
	}

	if(receiveStartByte == startByte_)
	{
		if(receiveCount == 9)
		{
			checkSum = 0;
			for(auto i : receiveDataArr)checkSum += i;
			if(checkSum == receiveCheckSum)
			{
				setSpeed =
						(int32_t)receiveDataArr[0] << 24|
						(int32_t)receiveDataArr[1] << 16|
						(int32_t)receiveDataArr[2] << 8 |
						(int32_t)receiveDataArr[3] ;
				setAngle =
						(int32_t)receiveDataArr[4] << 24|
						(int32_t)receiveDataArr[5] << 16|
						(int32_t)receiveDataArr[6] << 8 |
						(int32_t)receiveDataArr[7] ;

				if(nowSequence_ == sequenceName::start || nowSequence_ == sequenceName::waitCommand)
				{
					if(receiveDataCheck(setSpeed, setAngle))
					{
						launcherMechanism_.setThrowingSpeed((double)setSpeed);
						setLauncherAngleValue_ = setAngle;

						receiveCmd_ = receiveOrderFormat::throwShagai;
					}
				}

			}

			receiveCount = 0;
		}
		else
		{
			receiveCount++;
		}
	}
	else
	{
		receiveCount = 0;
	}
}

