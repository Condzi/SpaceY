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
		typedef Message<cstr_t> logMessage_t;
		typedef Message<int32_t> scrollMessage_t;

		std::array<sf::Text*, CONSOLE_VIEW_BUFFER> logsToDraw;

		void Init() override
		{
			this->logOnTop = CONSOLE_VIEW_BUFFER - 1;
		}

		void Update() override
		{
			auto& messenger = *this->context.messenger;
			auto logsToAdd = messenger.GetAllMessages<cstr_t>( MESSAGE_CONSOLE_ADD_LOG );
			auto scrollUp = messenger.GetUniqueMessage<int32_t>( MESSAGE_CONSOLE_SCROLL_UP );
			auto scrollDown = messenger.GetUniqueMessage<int32_t>( MESSAGE_CONSOLE_SCROLL_DOWN );

			bool logsNeedUpdate = false;
			if ( !logsToAdd.empty() )
			{
				this->handleLogAdd( std::move( logsToAdd ) );
				logsNeedUpdate = true;
			}
			if ( scrollUp || scrollDown )
			{
				this->handleScrolls( scrollUp, scrollDown );
				logsNeedUpdate = true;
			}

			//if ( logsNeedUpdate )
			this->updateLogsToDraw();
		}

	private:
		std::array<cstr_t, CONSOLE_CAPACITY> logs;
		// If we have id of log on top we can easly calculate interval of logs to draw.
		uint8_t logOnTop;

		void handleLogAdd( std::vector<logMessage_t*>& logsToAdd )
		{
			// Shift the array.
			std::rotate( this->logs.rbegin(), this->logs.rbegin() + logsToAdd.size(), this->logs.rend() );

			CON_ASSERT( logsToAdd.size() < CONSOLE_CAPACITY, "Console buffer overflow" );
			for ( uint8_t i = 0; i < logsToAdd.size(); i++ )
			{
				this->logs[i] = logsToAdd[i]->data;
				logsToAdd[i]->safeDelete = true;
			}
		}

		void handleScrolls( scrollMessage_t* up, scrollMessage_t* down )
		{
			int8_t finalOffset = 0;
			if ( up )
			{
				finalOffset -= 1;
				up->safeDelete = true;
			}
			if ( down )
			{
				finalOffset += 1;
				down->safeDelete = true;
			}

			int8_t offsetResult = this->logOnTop + finalOffset;
			if ( offsetResult <= CONSOLE_VIEW_BUFFER - 1 )
				this->logOnTop = CONSOLE_VIEW_BUFFER - 1;
			else if ( offsetResult >= CONSOLE_CAPACITY - 1 )
				this->logOnTop = CONSOLE_CAPACITY - 1;
			else
				this->logOnTop += finalOffset;
		}

		void updateLogsToDraw()
		{
			for ( uint8_t i = 0; i < CONSOLE_VIEW_BUFFER; i++ )
				logsToDraw[i]->setString( logs[this->logOnTop - i] );
		}
	};
}