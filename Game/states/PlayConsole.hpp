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

namespace con {
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
		laptopBG.GetComponent<DrawableComponent>().drawLayer = LAYER_BACKGROUND;
		auto laptopSprite = laptopBG.GetComponent<DrawableComponent>().object.GetAsSprite();

		laptopSprite->setTexture( *this->context.resourceCache->GetTexture( TEXTURE_ATLAS ) );
		laptopSprite->setTextureRect( { 0, 0, 352, 357 } );
		float lapScale = this->context.settings->GetInt( "WINDOW", "DESIGNED_Y" ) / 357.0f;
		laptopSprite->setScale( lapScale, lapScale );
		laptopSprite->setPosition( this->context.settings->GetInt( "WINDOW", "DESIGNED_X" ) / 2.0f - laptopSprite->getGlobalBounds().width / 2, this->context.settings->GetInt( "WINDOW", "DESIGNED_Y" ) / 2.0f - laptopSprite->getGlobalBounds().height / 2 );

		auto& console = this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_CONSOLE, this->context );

		this->addTexts( console.GetComponent<ConsoleScript>(), ( Vec2f( laptopSprite->getPosition() ) + 16 * lapScale ) );
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
	// TODO: Later create structure to hold information about console.
	// How big the screen is, what font is used - this is needed for rendering. 
	void addTexts( ConsoleScript& consoleScript, const Vec2f startPosition )
	{
		const auto& font = *this->context.resourceCache->GetFont( FONT_CONSOLAS );
		const float offset = 1.0f;
		sf::Text testText( "ABCDEFGHIJ", font, CONSOLE_TEXT_SIZE );
		const Vec2f textMaxSize( CONSOLE_MAX_TEXT_WIDTH, testText.getGlobalBounds().height );

		Vec2f prevPos = startPosition;
		for ( uint8_t i = 0; i < CONSOLE_VIEW_BUFFER; i++ ) {
			auto& textEntity = this->context.entityFactory->CreateEntity( this->context.entityManager->CreateEntity(), ENTITY_TEXT_CONSOLE, this->context );
			textEntity.GetComponent<PositionComponent>().x = prevPos.x;
			textEntity.GetComponent<PositionComponent>().y = prevPos.y;
			auto text = textEntity.GetComponent<DrawableComponent>().object.GetAsText();

			text->setFont( font );
			text->setCharacterSize( CONSOLE_TEXT_SIZE );
			prevPos.Set( startPosition.x, prevPos.y + textMaxSize.y * offset );
			LOG( prevPos.AsString(), INFO, CONSOLE );
		}
	}
};
}