/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Config.hpp>

namespace con
{
	enum state_t : stateID_t
	{
		STATE_EXIT = EXIT_STATE,
		STATE_DEBUG_DATA = DEBUG_DATA_STATE,
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
		// Core systems, don't touch!
		SYSTEM_POSITION_UPDATE = 0,
		SYSTEM_SIMPLE_PHYSIC,
		SYSTEM_SCRIPT_UPDATE,
		SYSTEM_RENDERER,
	};

	enum group_t : groupID_t
	{
		GROUP_MENU_STATE = 0,
		GROUP_PLAY_STATE_CONSOLE,
		GROUP_PAUSE_STATE
	};

	enum resources_t : resourceID_t
	{
		TEXTURE_SHEET_PLACEHOLDER = 0,

		FONT_CONSOLAS,

		TEXT_CONSOLE_LINE
	};

	enum resourcePriority_t : resourcePriorityID_t
	{
		RESOURCE_MULTISTATE = 0,
		RESOURCE_PLAY_CONSOLE
	};

	enum entity_t : uint8_t
	{
		ENTITY_CONSOLE = 0,
		ENTITY_TEXT_CONSOLE
	};

	enum drawLayer_t : int8_t
	{
		LAYER_BACKGROUND = 0,
		LAYER_TEXT
	};

	enum message_t : messageID_t
	{
		MESSAGE_CONSOLE_ADD_LOG,
		MESSAGE_CONSOLE_SCROLL_UP,
		MESSAGE_CONSOLE_SCROLL_DOWN
	};
}