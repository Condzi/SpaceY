/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/state/State.hpp>
#include <Core/ecs/EntityManager.hpp>
#include <Core/resourceManaging/ResourceHolder.hpp>
#include <Core/Vec2.hpp>

#include <Game/EntityCreators.hpp>

namespace con
{
	class PlayConsoleState final :
		public State
	{
	public:
		PlayConsoleState( StateStack& stack, Context cont ) :
			State( stack, cont )
		{}

		stateID_t GetID() const override
		{
			return STATE_PLAY_CONSOLE;
		}

		void OnPush() override
		{
			this->StartThread();

			auto& console = this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_CONSOLE, this->context );

			this->addTexts( { 200.0f, 200.0f }, 50, console.GetComponent<ConsoleScript>() );
		}

		void OnPop() override
		{
			// Clean up.
			for ( auto entity : this->context.entityManager->GetEntitiesByGroup( GROUP_PLAY_STATE_CONSOLE ) )
				entity->Kill();
			this->context.resourceCache->DeleteAllResourcesByPriority( RESOURCE_PLAY_CONSOLE );
		}

		void Update()
		{
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::A ) )
				this->context.messenger->AddMessage( MESSAGE_CONSOLE_ADD_LOG, ( cstr_t )"Hello! Woo! \1" );
			if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				this->context.messenger->AddMessage( MESSAGE_CONSOLE_SCROLL_DOWN, (int32_t)-1 );
			if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				this->context.messenger->AddMessage( MESSAGE_CONSOLE_SCROLL_UP, (int32_t)1 );
		}

	private:
		void addTexts( const Vec2f& positionStart, const uint8_t fontSize, ConsoleScript& consoleScript )
		{
			auto& textCache = this->context.resourceCache->uiTexts;
			textCache.reserve( CONSOLE_VIEW_BUFFER );
			auto& font = *this->context.resourceCache->GetFont( FONT_CONSOLAS );

			Vec2f prevPos = positionStart;
			float textHeight = 0;
			std::for_each( consoleScript.logsToDraw.rbegin(), consoleScript.logsToDraw.rend(), [&]( auto& text )
			{
				textCache.emplace_back( std::make_unique<uiTextResource_t>( RESOURCE_PLAY_CONSOLE, TEXT_CONSOLE_LINE ) );
				text = textCache.back().get();

				text->setFont( font );
				text->setCharacterSize( fontSize );
				if ( textHeight == 0 )
				{
					text->setString( "blah" );
					textHeight = text->getGlobalBounds().height;
					text->setString( "" );
				} else
					prevPos.Set( positionStart.x, prevPos.y + textHeight + textHeight / 10.0f );

				auto& textEntity = this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_TEXT_CONSOLE, this->context );
				textEntity.GetComponent<DrawableTextScript>().textToDraw = text;
				textEntity.GetComponent<PositionComponent>().x = prevPos.x;
				textEntity.GetComponent<PositionComponent>().y = prevPos.y;
				this->context.messenger->AddMessage( MESSAGE_CONSOLE_ADD_LOG, ( cstr_t )"LOOL" );
			} );
		}
	};
}