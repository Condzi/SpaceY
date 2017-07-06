/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

// std::rotate
#include <algorithm>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Core/components/Script.hpp>
#include <Core/resourceManaging/ResourceHolder.hpp>
#include <Core/Context.hpp>
#include <Core/ecs/Messaging.hpp>

#include <Game/Enums.hpp>
#include <Game/Config.hpp>

namespace con
{
	struct ConsoleScript final :
		ScriptComponent
	{
		typedef Message<cstr_t> logMessage_t;

		void Init() override
		{
			this->logOnTop = CONSOLE_VIEW_BUFFER - 1;
		}

		void Update() override
		{
			auto& messenger = *this->context.messenger;
			auto logsToAdd = messenger.GetAllMessages<cstr_t>( MESSAGE_CONSOLE_ADD_LOG );

			int8_t wheelDelta = 0;
			auto events = messenger.GetAllMessages<sf::Event>( MESSAGE_INPUT_EVENT );
			for ( auto event : events )
				if ( event->data.type == sf::Event::MouseWheelScrolled )
					// When was raw data then causes ugly behaviour of scrolling few lines at once.
					wheelDelta = event->data.mouseWheelScroll.delta /*> 0 ? 1 : -1*/;

			bool logsNeedUpdate = false;
			if ( !logsToAdd.empty() )
			{
				this->handleLogAdd( std::move( logsToAdd ) );
				logsNeedUpdate = true;
			}
			if ( wheelDelta )
			{
				this->handleScrolls( wheelDelta );
				logsNeedUpdate = true;
			}

			if ( logsNeedUpdate )
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

		void handleScrolls( const int8_t wheelDelta )
		{
			int8_t offsetResult = this->logOnTop + wheelDelta;
			if ( offsetResult <= CONSOLE_VIEW_BUFFER - 1 )
				this->logOnTop = CONSOLE_VIEW_BUFFER - 1;
			else if ( offsetResult >= CONSOLE_CAPACITY - 1 )
				this->logOnTop = CONSOLE_CAPACITY - 1;
			else
				this->logOnTop += wheelDelta;
		}

		void updateLogsToDraw()
		{
			auto textEntities = this->context.entityManager->GetEntitiesWithSignature( ENTITY_TEXT_CONSOLE );
			CON_ASSERT( textEntities.size() == CONSOLE_VIEW_BUFFER, "There is more console lines of text than declared" );

			for ( uint8_t i = 0; i < CONSOLE_VIEW_BUFFER; i++ )
			{
				auto textPtr = textEntities[i]->GetComponent<DrawableComponent>().object.GetAsText();
				textPtr->setString( logs[this->logOnTop - i]);
				float logWidth = textPtr->getGlobalBounds().width;
				if ( logWidth > CONSOLE_MAX_TEXT_WIDTH )
					LOG( "Log text for console is too big; graphic bugs will occur. (" << logWidth << '/' << CONSOLE_MAX_TEXT_WIDTH, WARNING, CONSOLE );
			}
		}
	};
}