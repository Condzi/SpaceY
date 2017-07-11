/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/
#pragma once

#include <cinttypes>
#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <Core/Assert.hpp>
#include <Core/ecs/Component.hpp>

namespace con {
/*
===============================================================================
Created by: Condzi
	Drawable Object class provides inteface for manipulating sf::Drawable children:
	sf::Text, sf::Sprite, sf::RectangleShape, sf::CircleShape. Use sf:Drawable
	to check if DrawableObject has already any darwable in it. WARNING: There
	are no checks for Getters, so if you first use GetAsText and later GetAsSprite
	then undefined behaviour will occur - use same getters all time! If you REALLY
	need to change type - use Clear() method. If you want only to change its position,
	use GetAsTransformable.

===============================================================================
*/
class DrawableObject final
{
public:
	sf::Text* GetAsText()
	{
		return this->initAndReturn<sf::Text>();
	}
	sf::Sprite* GetAsSprite()
	{
		return this->initAndReturn<sf::Sprite>();
	}
	sf::RectangleShape* GetAsRectShape()
	{
		return this->initAndReturn<sf::RectangleShape>();
	}
	sf::CircleShape* GetAsCircleShape()
	{
		return this->initAndReturn<sf::CircleShape>();
	}
	sf::Drawable* GetAsDrawable()
	{
		return this->object.get();
	}
	sf::Transformable* GetAsTransformable()
	{
		return dynamic_cast<sf::Transformable*>( this->object.get() );
	}

	void Clear()
	{
		this->object.reset();
	}

private:
	std::unique_ptr<sf::Drawable> object;

	template <typename T>
	T* initAndReturn()
	{
		CON_STATIC_ASSERT( std::is_base_of_v<sf::Drawable, T>, "Wrong use of T* initAndReturn<T>, T must inherit from sf::Drawable" );
		if ( !this->object )
			this->object = std::make_unique<T>();

		return dynamic_cast<T*>( this->object.get() );
	}
};

/*
===============================================================================
Created by: Condzi
	Drawable Component structure. It has DrawableObject and draw layer (-128 to 127).

===============================================================================
*/
struct DrawableComponent :
	Component
{
	int8_t drawLayer = 0;
	DrawableObject object;
};
}
