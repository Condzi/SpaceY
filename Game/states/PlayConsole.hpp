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

			this->addTexts( console.GetComponent<ConsoleScript>() );
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
				this->context.messenger->AddMessage( MESSAGE_CONSOLE_ADD_LOG, ( cstr_t )"Hello! Woo!" );
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				this->context.messenger->AddMessage( MESSAGE_CONSOLE_SCROLL_DOWN, (int32_t)-1 );
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				this->context.messenger->AddMessage( MESSAGE_CONSOLE_SCROLL_UP, (int32_t)1 );
		}

	private:
		void addTexts( ConsoleScript& consoleScript )
		{
			auto& textCache = this->context.resourceCache->uiTexts;
			textCache.reserve( CONSOLE_VIEW_BUFFER );
			const auto& font = *this->context.resourceCache->GetFont( FONT_CONSOLAS );
			const Vec2f center( this->context.settings->GetInt( "WINDOW", "DESIGNED_X" ) / 2, this->context.settings->GetInt( "WINDOW", "DESIGNED_Y" ) / 2 );

			sf::Text testText( "test", font, CONSOLE_TEXT_SIZE );
			const Vec2f textMaxSize( CONSOLE_MAX_TEXT_WIDTH, testText.getGlobalBounds().height );
			const Vec2f startPosition( center.x - textMaxSize.x / 2, center.y - textMaxSize.y * 1.1f * ( CONSOLE_VIEW_BUFFER / 2 ) );

			// Removing wrong offset for first text.
			Vec2f prevPos( startPosition.x, startPosition.y - textMaxSize.y * 1.1f );
			for ( auto& text : consoleScript.logsToDraw )
			{
				textCache.emplace_back( std::make_unique<uiTextResource_t>( RESOURCE_PLAY_CONSOLE, TEXT_CONSOLE_LINE ) );
				text = textCache.back().get();

				text->setFont( font );
				text->setCharacterSize( CONSOLE_TEXT_SIZE );
				prevPos.Set( startPosition.x, prevPos.y + textMaxSize.y * 1.1f );

				auto& textEntity = this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_TEXT_CONSOLE, this->context );
				textEntity.GetComponent<DrawableTextScript>().textToDraw = text;
				textEntity.GetComponent<PositionComponent>().x = prevPos.x;
				textEntity.GetComponent<PositionComponent>().y = prevPos.y;
			}
		}
	};
}