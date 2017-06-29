/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/
#pragma once

#include <cinttypes>

#include <SFML/Graphics/Sprite.hpp>

#include <Core/ecs/Component.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Drawable Component structure. It has sprite and draw layer (-128 to 127).

	===============================================================================
	*/
	struct DrawableComponent final : 
		Component
	{
		sf::Sprite sprite;
		int8_t drawLayer = 0;
	};
}
