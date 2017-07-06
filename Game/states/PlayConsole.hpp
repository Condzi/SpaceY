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

			this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_PLAY_CONSOLE_STATE_GAME_MASTER, this->context );


			auto& laptopBG = this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_SPRITE, this->context );
			laptopBG.GetComponent<DrawableComponent>().object.GetAsSprite()->setTexture( *this->context.resourceCache->GetTexture( TEXTURE_ATLAS ) );
			laptopBG.GetComponent<DrawableComponent>().object.GetAsSprite()->setTextureRect( { 0, 0, 90,86 } );

			// IMPORTANT: !!FIXME!!
			// HUUUGE TEMPORARY CODE, FIX ME PLEASE
			const Vec2f center( this->context.settings->GetInt( "WINDOW", "DESIGNED_X" ) / 2, this->context.settings->GetInt( "WINDOW", "DESIGNED_Y" ) / 2.5f );
			sf::Text testText( "test", *this->context.resourceCache->GetFont( FONT_CONSOLAS ), CONSOLE_TEXT_SIZE );
			const Vec2f textMaxSize( CONSOLE_MAX_TEXT_WIDTH, testText.getGlobalBounds().height );
			const Vec2f startPosition( center.x - textMaxSize.x / 2, center.y - textMaxSize.y * 1.1f * ( CONSOLE_VIEW_BUFFER / 2 ) );
			laptopBG.GetComponent<DrawableComponent>().object.GetAsSprite()->setScale( textMaxSize.x / 80, textMaxSize.y * CONSOLE_VIEW_BUFFER * 1.1f / 60 );
			laptopBG.GetComponent<PositionComponent>().x = startPosition.x - 5 * laptopBG.GetComponent<DrawableComponent>().object.GetAsSprite()->getScale().x;
			laptopBG.GetComponent<PositionComponent>().y = startPosition.y - 5 * laptopBG.GetComponent<DrawableComponent>().object.GetAsSprite()->getScale().y;


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
		{}

	private:
		void addTexts( ConsoleScript& consoleScript )
		{
			const auto& font = *this->context.resourceCache->GetFont( FONT_CONSOLAS );
			const Vec2f center( this->context.settings->GetInt( "WINDOW", "DESIGNED_X" ) / 2, this->context.settings->GetInt( "WINDOW", "DESIGNED_Y" ) / 2.5f );

			sf::Text testText( "test", font, CONSOLE_TEXT_SIZE );
			const Vec2f textMaxSize( CONSOLE_MAX_TEXT_WIDTH, testText.getGlobalBounds().height );
			const Vec2f startPosition( center.x - textMaxSize.x / 2, center.y - textMaxSize.y * 1.1f * ( CONSOLE_VIEW_BUFFER / 2 ) );

			// Removing wrong offset for first text.
			Vec2f prevPos( startPosition.x, startPosition.y - textMaxSize.y * 1.1f );
			for ( uint8_t i = 0; i < CONSOLE_VIEW_BUFFER; i++ )
			{
				auto& textEntity = this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_TEXT_CONSOLE, this->context );
				textEntity.GetComponent<PositionComponent>().x = prevPos.x;
				textEntity.GetComponent<PositionComponent>().y = prevPos.y;
				auto text = textEntity.GetComponent<DrawableComponent>().object.GetAsText();

				text->setFont( font );
				text->setCharacterSize( CONSOLE_TEXT_SIZE );
				prevPos.Set( startPosition.x, prevPos.y + textMaxSize.y * 1.1f );
			}
		}
	};
}