/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Config.hpp>

namespace con {
enum state_t : stateID_t
{
	STATE_EXIT = (stateID_t)coreStates_t::EXIT,
	STATE_DEBUG_DATA = (stateID_t)coreStates_t::DEBUG_DATA,
	STATE_LOADING_SCREEN,
	STATE_MENU,
	// Console screen
	STATE_PLAY_CONSOLE,
	// Just a placeholder
	STATE_PLAY_PLACEHOLDER,
	STATE_PAUSE
};

enum system_t : systemID_t
{
	SYSTEM_POSITION_UPDATE = (systemID_t)coreSystems_t::POSITION_UPDATE,
	SYSTEM_SIMPLE_PHYSIC = (systemID_t)coreSystems_t::SIMPLE_PHYSIC,
	SYSTEM_SCRIPT_UPDATE = (systemID_t)coreSystems_t::SCRIPT_UPDATE,
	SYSTEM_RENDERER = (systemID_t)coreSystems_t::RENDERER
};

enum group_t : groupID_t
{
	GROUP_MENU_STATE = 0,
	GROUP_PLAY_STATE_CONSOLE,
	GROUP_PAUSE_STATE
};

enum resources_t : resourceID_t
{
	TEXTURE_ATLAS = 0,

	FONT_CONSOLAS
};

enum resourcePriority_t : resourcePriorityID_t
{
	RESOURCE_MULTISTATE = 0,
	RESOURCE_PLAY_CONSOLE
};

enum entity_t : uint8_t
{
	ENTITY_CONSOLE = 0,
	ENTITY_TEXT_CONSOLE,
	// Misc sprite, background or something.
	ENTITY_SPRITE,

	ENTITY_PLAY_CONSOLE_STATE_GAME_MASTER
};

enum drawLayer_t : int8_t
{
	LAYER_BACKGROUND = 0,
	LAYER_TEXT
};

enum message_t : messageID_t
{
	MESSAGE_INPUT_EVENT = (messageID_t)coreMessages_t::INPUT_EVENT,
	MESSAGE_CONSOLE_ADD_LOG
};
}