/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <Core/components/Script.hpp>
#include <Core/components/Drawable.hpp>
#include <Core/ecs/Entity.hpp>
#include <Core/Context.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Inherits from ScriptComponent; gives you acces to OnButtonClick method.
		Its Update method detects if button is clicked and calls OnButtonClick.

	===============================================================================
	*/
	struct ButtonScript :
		ScriptComponent
	{
		virtual void OnButtonClick() {}

		void Update() override
		{
			auto mousePos = this->context.window->mapPixelToCoords( sf::Mouse::getPosition( *this->context.window ) );
			auto& drawableComponent = this->entity->GetComponent<DrawableComponent>();
			// IDEA: Move this code to InitBounds or something?

			sf::FloatRect buttonBounds( 0, 0, 0, 0 );

			if ( !drawableComponent.object.GetAsDrawable() )
				LOG( "Drawable not set for button", WARNING, BOTH );
			else if ( *drawableComponent.object.GetAsText() )
				buttonBounds = getRealTextBounds( **drawableComponent.object.GetAsText() );
			else if ( *drawableComponent.object.GetAsSprite() )
				buttonBounds = ( *drawableComponent.object.GetAsSprite() )->getGlobalBounds();
			else if ( *drawableComponent.object.GetAsRectShape() )
				buttonBounds = ( *drawableComponent.object.GetAsRectShape() )->getGlobalBounds();
			else if ( *drawableComponent.object.GetAsCircleShape() )
				buttonBounds = ( *drawableComponent.object.GetAsCircleShape() )->getGlobalBounds();

			if ( buttonBounds.contains( mousePos.x, mousePos.y ) &&
				sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
				this->OnButtonClick();
		}
	};
}