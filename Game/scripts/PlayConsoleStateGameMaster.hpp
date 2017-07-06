/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/components/Script.hpp>
#include <Core/ecs/EntityManager.hpp>
#include <Core/ecs/Messaging.hpp>
#include <Core/time/Time.hpp>

#include <Game/scripts/console/ConsoleScript.hpp>
#include <Game/Enums.hpp>

namespace con
{
	struct PlayConsoleStateGameMaster final :
		ScriptComponent
	{
		void Init()
		{
			this->context.messenger->AddMessage( MESSAGE_CONSOLE_ADD_LOG, consoleMessage_t( "+=+=+= FALCON 1 STARTUP =+=+=+" ) );
		}

		uint8_t wildCounter = 0;
		Time wildTime;
		void Update() override
		{
			wildTime += Time::FRAME_TIME;
			wildCounter++;
			if ( wildTime < asMilliseconds( 500 ) )
				return;
			wildTime = 0;
			auto messenger = this->context.messenger; 
			messenger->AddMessage( MESSAGE_CONSOLE_ADD_LOG, consoleMessage_t( std::to_string(+(++wildCounter)) + " - wild counter value", consoleMessage_t::WARNING ) );
			messenger->AddMessage( MESSAGE_CONSOLE_ADD_LOG, consoleMessage_t( "It's rather a long message to localize so I'm worried about performance with std::string", consoleMessage_t::INFO ) );
		}
	};
}