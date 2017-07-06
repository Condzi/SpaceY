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

		std::string message = "";
		messageType_t type = INFO;

		consoleMessage_t( std::string msg = "", uint8_t msgType = INFO ) :
			message( std::move( msg ) ),
			type( static_cast<messageType_t>( msgType ) )
		{}
	};
}