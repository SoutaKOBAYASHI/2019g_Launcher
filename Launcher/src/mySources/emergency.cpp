/*
 * emergency.cpp
 *
 *  Created on: 2019/04/06
 *      Author: User
 */

#include <emergencty.hpp>

IO_sigPins<ioName::sig7, ioState::input, pinPullDirection::up> emergencySwitch;
