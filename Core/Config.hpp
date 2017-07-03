/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Config.hpp>

// Forward declarations.
namespace sf
{
	template <typename T>
	class Rect;
	class Text;
}

namespace con
{
	constexpr const char* GAME_NAME = "SpaceY";
	// Amount of keys pressed / released stored in history
	constexpr uint8_t INPUT_KEY_HISTORY = 128;

	typedef int16_t stateID_t;
	typedef int8_t resourcePriorityID_t;
	typedef int8_t resourceID_t;
	typedef const char* cstr_t;

	enum class coreStates_t : stateID_t
	{
		EXIT = 0,
		DEBUG_DATA
	};

	enum class coreMessages_t : messageID_t
	{
		INPUT_EVENT = 0
		//MESSAGE_PHYSIC_COLLISION
	};

	// IDEA: Maybe move this to functions.hpp ?
	sf::Rect<float> getRealTextBounds( const sf::Text& text );
}

// IDEA: Maybe move this macro to Macros.hpp? Along with Assertions.
#define CON_UNUSED_PARAM( x ) ( ( void )( x ) )