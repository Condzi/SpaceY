#pragma once

#include <Core/ecs/Config.hpp>

// Forward declarations.
namespace sf
{
	struct FloatRect;
	class Text;
}

namespace con
{
	// Forward declarations c.d
	enum Key;

	constexpr const char* GAME_NAME = "SpaceY";
	// Amount of keys pressed / released stored in history
	constexpr uint8_t INPUT_KEY_HISTORY = 128;

	typedef int16_t stateID_t;
	typedef int8_t resourcePriorityID_t;
	typedef int8_t resourceID_t;
	typedef const char* cstr_t;

	enum class coreStates_t : stateID_t
	{
		EXIT = -1,
		DEBUG_DATA
	};

	// IDEA: Maybe move this to functions.hpp ?
	sf::FloatRect getRealTextBounds( const sf::Text& text );

	bool isKeyPressed( Key key );
}

// IDEA: Maybe move this macro to Macros.hpp? Along with Assertions.
#define CON_UNUSED_PARAM( x ) ( ( void )( x ) )