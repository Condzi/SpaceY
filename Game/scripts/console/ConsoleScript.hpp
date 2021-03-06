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
#include <Game/scripts/console/ConsoleMessage.hpp>

namespace con {
struct ConsoleScript final :
	ScriptComponent
{
	using logMessage_t = Message<consoleMessage_t>;

	void Init() override
	{
		this->logOnTop = CONSOLE_VIEW_BUFFER - 1;
		this->signature = createComponentSignature( getComponentTypeID<EntityTagComponent>() );
	}

	void Update() override
	{
		auto& messenger = *this->context.messenger;
		auto logsToAdd = messenger.GetAllMessages<consoleMessage_t>( MESSAGE_CONSOLE_ADD_LOG );

		int8_t wheelDelta = 0;
		auto events = messenger.GetAllMessages<sf::Event>( MESSAGE_INPUT_EVENT );
		for ( auto event : events )
			if ( event->data.type == sf::Event::MouseWheelScrolled )
				wheelDelta = static_cast<int8_t>( event->data.mouseWheelScroll.delta );

		bool logsNeedUpdate = false;
		if ( !logsToAdd.empty() ) {
			this->handleLogAdd( logsToAdd );
			logsNeedUpdate = true;
		}
		if ( wheelDelta ) {
			this->handleScrolls( wheelDelta );
			logsNeedUpdate = true;
		}

		if ( logsNeedUpdate )
			this->updateLogsToDraw();
	}

private:
	std::array<consoleMessage_t, CONSOLE_CAPACITY> logs;
	componentBitset_t signature;
	// If we have id of log on top we can easily calculate interval of logs to draw.
	uint8_t logOnTop;

	void handleLogAdd( std::vector<logMessage_t*>& logsToAdd )
	{
		CON_ASSERT( logsToAdd.size() < CONSOLE_CAPACITY, "Console buffer overflow" );

		// Shift the array.
		std::rotate( this->logs.rbegin(), this->logs.rbegin() + logsToAdd.size(), this->logs.rend() );
		for ( uint8_t i = 0; i < logsToAdd.size(); i++ ) {
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
		auto textEntities = this->context.entityManager->GetEntitiesWithSignature( this->signature );
		textEntities.erase( std::remove_if( textEntities.begin(), textEntities.end(),
							[]( Entity* e )
		{
			return e->GetComponent<EntityTagComponent>().tag != ENTITY_TEXT_CONSOLE;
		}
		), textEntities.end() );

		CON_ASSERT( textEntities.size() == CONSOLE_VIEW_BUFFER, "There is more console lines of text than declared" );

		for ( uint8_t i = 0; i < CONSOLE_VIEW_BUFFER; i++ ) {
			auto textPtr = textEntities[i]->GetComponent<DrawableComponent>().object.GetAsText();
			auto& log = logs[this->logOnTop - i];
			textPtr->setString( log.message );
			textPtr->setFillColor( [log]() -> sf::Color
			{
				switch ( log.type ) {
					case consoleMessage_t::INFO: return sf::Color::White;
					case consoleMessage_t::WARNING: return sf::Color::Yellow;
					case consoleMessage_t::ERROR: return sf::Color::Red;
					default: return sf::Color::Magenta;
				}
			}( ) );
			float logWidth = textPtr->getGlobalBounds().width;
			if ( logWidth > CONSOLE_MAX_TEXT_WIDTH )
				LOG( "Log text for console is too big; graphic bugs will occur. (" << logWidth << '/' << CONSOLE_MAX_TEXT_WIDTH, WARNING, CONSOLE );
		}
	}
};
}