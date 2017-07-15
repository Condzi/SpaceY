/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Config.hpp>

// Forward declarations.
namespace sf {
template <typename T>
class Rect;
class Text;
}

namespace con {

using stateID_t = int16_t;
using resourcePriorityID_t = int8_t;
using resourceID_t = int8_t;
using cstr_t = const char*;

constexpr cstr_t PATH_ENGINE_SETTINGS = "engine.ini";
constexpr cstr_t PATH_GAME_SETTINGS = "game.ini";
constexpr uint8_t MAX_SETTINGS_RECORDS = 255;


enum class coreStates_t : stateID_t
{
	EXIT = 0,
	DEBUG_DATA
};

enum class coreSystems_t : systemID_t
{
	POSITION_UPDATE = 0,
	SIMPLE_PHYSIC,
	SCRIPT_UPDATE,
	RENDERER
};

enum class coreMessages_t : messageID_t
{
	INPUT_EVENT = 0
	//MESSAGE_PHYSIC_COLLISION
};

// IDEA: Maybe move this to functions.hpp ?
sf::Rect<float> getRealTextBounds( const sf::Text& text );
}