/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

// std::rotate
#include <algorithm>

#include <Core/components/Script.hpp>
#include <Core/resourceManaging/ResourceHolder.hpp>
// For context structure.
#include <Core/state/State.hpp>
#include <Core/ecs/Messaging.hpp>

#include <Game/Enums.hpp>
#include <Game/Config.hpp>

namespace con
{
	struct ConsoleScript :
		ScriptComponent
	{
		typedef message_t<cstr_t> logMessage_t;
		typedef message_t<int32_t> scrollMessage_t;

		void Init() override
		{
			this->logOnTop = CONSOLE_VIEW_BUFFER;
			this->logs[0] = "SYSTEM_INIT";
		}

		void Update() override
		{
			auto& messenger = *this->context.messenger;
			auto logsToAdd = messenger.GetAllMessages<cstr_t>( MESSAGE_CONSOLE_ADD_LOG );
			auto scrollsUp = messenger.GetAllMessages<int32_t>( MESSAGE_CONSOLE_SCROLL_UP );
			auto scrollsDown = messenger.GetAllMessages<int32_t>( MESSAGE_CONSOLE_SCROLL_DOWN );

			if ( !logsToAdd.empty() )
				this->handleLogAdd( std::move( logsToAdd ) );
			if ( !scrollsUp.empty() || scrollsDown.empty() )
				this->handleScrolls( std::move( scrollsUp ), std::move( scrollsDown ) );
		}

	private:
		std::array<cstr_t, CONSOLE_CAPACITY> logs;
		std::array<sf::Text*, CONSOLE_VIEW_BUFFER> logsToDraw;
		// If we have id of log on top we can easly calculate interval of logs to draw.
		uint8_t logOnTop;

		void handleLogAdd( const std::vector<logMessage_t*>& logsToAdd )
		{
			// Shift the array.
			std::rotate( this->logs.rbegin(), this->logs.rbegin() + logsToAdd.size(), this->logs.rend() );

			CON_ASSERT( logsToAdd.size() < CONSOLE_CAPACITY, "Console buffer overflow" );
			for ( uint8_t i = 0; i < logsToAdd.size(); i++ )
				this->logs[i] = logsToAdd[i]->data;
		}

		void handleScrolls( const std::vector<scrollMessage_t*>& up, const std::vector<scrollMessage_t*>& down )
		{
			int16_t finalOffset = 0;
			for ( auto upVal : up )
				finalOffset += upVal->data;
			for ( auto downVal : down )
				finalOffset += downVal->data;

			int16_t offsetResult = finalOffset + this->logOnTop;
			if ( offsetResult <= 0 )
				this->logOnTop = 0 + CONSOLE_VIEW_BUFFER;
			else if ( offsetResult >= CONSOLE_CAPACITY )
				this->logOnTop = CONSOLE_CAPACITY;
				
			this->logOnTop += finalOffset;
		}
	};
}