#pragma once

#include <SFML/Graphics/Text.hpp>

#include <Core/ecs/Config.hpp>

namespace con
{
	constexpr const char* GAME_NAME = "ConEngine";
	constexpr int16_t EXIT_STATE = -1;
	constexpr int16_t DEBUG_DATA_STATE = 0;

	typedef int16_t stateID_t;
	typedef int8_t resourcePriorityID_t;
	typedef int8_t resourceID_t;
	typedef const char* cstr_t;

	// IDEA: Maybe move this to functions.hpp ?
	inline sf::FloatRect getRealTextBounds( const sf::Text& text )
	{
		return sf::FloatRect(
			text.getPosition().x + ( text.getCharacterSize() * 3 ) / 50.0f,
			text.getPosition().y + ( text.getCharacterSize() * 15.3f ) / 50.0f,
			text.getGlobalBounds().width,
			text.getGlobalBounds().height
		);
	}
}

// IDEA: Maybe move this macro to Macros.hpp? Along with Assertions.
#define CON_UNUSED_PARAM( x ) ( ( void )( x ) )