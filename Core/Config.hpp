#pragma once

#include <Core/ecs/Config.hpp>

namespace con
{
	constexpr const char* GAME_NAME = "ConEngine";
	constexpr int16_t EXIT_STATE = -1;
	constexpr int16_t DEBUG_DATA_STATE = 0;

	typedef int16_t stateID_t;
	typedef int8_t resourcePriorityID_t;
	typedef int8_t resourceID_t;
}

// IDEA: Maybe move this macro to Macros.hpp? Along with Assertions.
#define CON_UNUSED_PARAM( x ) ( ( void )( x ) )