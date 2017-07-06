/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Config.hpp>

namespace con
{
	// Contains data about message to log into game console.
	struct consoleMessage_t final
	{
		enum messageType_t : uint8_t
		{
			INFO, WARNING, ERROR
		};

		cstr_t message = "";
		messageType_t type = INFO;

		consoleMessage_t( cstr_t msg = "", uint8_t msgType = INFO ) :
			message( msg ),
			type( static_cast<messageType_t>( msgType ) )
		{}
	};
}