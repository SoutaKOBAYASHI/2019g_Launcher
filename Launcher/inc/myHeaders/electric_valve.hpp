/*
 * electric_valve.h
 *
 *  Created on: 2019/02/28
 *      Author: User
 */

#ifndef MYHEADERS_ELECTRIC_VALVE_HPP_
#define MYHEADERS_ELECTRIC_VALVE_HPP_

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include <type_traits>
#include <utility>

class EV
{
public:
	EV();

	enum name : uint16_t
	{
		EV0	= 0x0100,
		EV1	= 0x0200,
		EV2	= 0x0400,
		EV3	= 0x0800,
		EV4	= 0x1000,
		EV5	= 0x2000,
		EV6	= 0x4000,
		EV7	= 0x8000
	};
	enum class state { Set, Reset };

	template<class Head, class...  valves>
	void setNewState(state newState, Head setEvHead, valves... setEvNumber)
	{
		static_assert(std::is_same_v<Head, name>, "It is not 'name' that type of second argument.");

		if(newState == state::Set)GPIO_SetBits(GPIOC, (uint16_t)setEvHead);
		else GPIO_ResetBits(GPIOC, (uint16_t)setEvHead);

		setNewState(newState, std::forward<valves>(setEvNumber)...);
	}

	virtual ~EV();

protected:
	void GPIO_PinsInit();
	inline void setNewState(state newState){}
};

#endif /* MYHEADERS_ELECTRIC_VALVE_HPP_ */
