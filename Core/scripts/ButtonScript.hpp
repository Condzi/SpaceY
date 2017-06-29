/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include <Core/components/Script.hpp>
#include <Core/components/Drawable.hpp>
#include <Core/ecs/Entity.hpp>
#include <Core/state/State.hpp>

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
			auto mousePos = this->context->window->mapPixelToCoords( sf::Mouse::getPosition( *this->context->window ) );
			auto buttonBounds = this->entity->GetComponent<DrawableComponent>().sprite.getGlobalBounds();

			if ( buttonBounds.contains( mousePos.x, mousePos.y ) &&
				sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
				this->OnButtonClick();
		}
	};
}