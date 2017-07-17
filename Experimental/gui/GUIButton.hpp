/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <bitset>
#include <vector>
#include <memory>

#include <Core/Vec2.hpp>

namespace con {

class GUIButton final : 
	public sf::Drawable
{
public:
	using Flags = std::bitset<1>;
	enum flag_t : uint8_t
	{
		SELECTED,
		CLICKED
	};

	GUIButton( Vec2f relPos, std::string title );

	void SetText( const std::string& title );
	void SetTextFont( const sf::Font& font );
	void SetSize( const Vec2f& size );
	void SetPosition( const Vec2f& relPos );
	void SetScreenSize( const Vec2f& size );
	void SetFlag( const flag_t flag, bool value );
	void Move( const Vec2f& offset );
	
	sf::FloatRect GetGlobalBounds() const;
	
	void Update();

private:
	Vec2f relativePosition;
	Vec2f screenSize;
	Flags flags;
	bool textNeedUpdate = true;
	bool positionsNeedsUpdate = true;

	sf::RectangleShape shape;
	sf::Text text;

	void updateText();
	void updatePositions();
	void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
};
}