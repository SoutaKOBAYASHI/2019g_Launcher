/*
 * emergencty.hpp
 *
 *  Created on: 2019/04/06
 *      Author: User
 */

#ifndef MYHEADERS_EMERGENCTY_HPP_
#define MYHEADERS_EMERGENCTY_HPP_

#include <board_io.hpp>
extern IO_sigPins<ioName::sig7, ioState::input, pinPullDirection::up> emergencySwitch;

#endif /* MYHEADERS_EMERGENCTY_HPP_ */
