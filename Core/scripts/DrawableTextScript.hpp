/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <Core/components/Script.hpp>
#include <Core/components/Drawable.hpp>
#include <Core/ecs/Entity.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Not inheritable. Simple draws given text (set DrawableTextScript::textToDraw
		pointer to some sf::Text value from resourceCache).

	===============================================================================
	*/
	struct DrawableTextScript final :
		ScriptComponent
	{
		sf::RenderTexture texture;
		sf::Sprite* spriteToRender = nullptr;
		sf::Text* textToDraw = nullptr;

		void Init()
		{
			// Try to set sprite. If DrawableTextScript is added before DrawableComponent we are accepting it to fail.
			this->setSpriteToRender( false );
		}

		void Update() override
		{
			if ( !this->spriteToRender )
				this->setSpriteToRender( true );
			if ( !this->textToDraw )
			{
				LOG( "Text to draw for DrawableTextScript is not set", WARNING, CONSOLE );
				return;
			}

			if ( this->previousText == this->textToDraw->getString() )
				return;

			this->previousText = this->textToDraw->getString();

			this->texture.create( static_cast<uint32_t>( this->textToDraw->getGlobalBounds().width ), static_cast<uint32_t>( this->textToDraw->getGlobalBounds().height * 2 ) );
			this->texture.clear( sf::Color::Transparent );
			this->texture.draw( *this->textToDraw );
			this->texture.display();

			this->spriteToRender->setTextureRect( { 0,0, static_cast<int>( this->textToDraw->getGlobalBounds().width ), static_cast<int>( this->textToDraw->getGlobalBounds().height * 2 ) } );
			this->spriteToRender->setTexture( this->texture.getTexture() );
		}

	private:
		// Keep track of text - if previous text is different from current textToDraw's then recreate texture.
		sf::String previousText = "";

		void setSpriteToRender( bool testAssert )
		{
			if ( testAssert )
				CON_ASSERT( this->entity->HasComponent<DrawableComponent>(), "Entity with DrawableTextScript must have DrawableComponent" );

			if ( !testAssert && !this->entity->HasComponent<DrawableComponent>() )
				return;

			auto& drawableComponent = this->entity->GetComponent<DrawableComponent>();
			this->spriteToRender = &drawableComponent.sprite;
		}
	};
}