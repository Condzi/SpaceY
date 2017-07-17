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

class GUIWindow final :
	public sf::Drawable
{
	// Size of the title bar in pixels, never changes.
	static constexpr float SIZE_TITLEBAR_Y = 20;
	static constexpr float SIZE_TITLEBAR_CHARACTER_SIZE = 16;

public:
	using Flags = std::bitset<3>;
	enum flag_t : uint8_t
	{
		NO_TITLE_BAR,
		GRABABLE,
		EXPANDED
	};

	GUIWindow( Vec2f relPos, std::string title );

	void SetTitleText( const std::string& text );
	void SetTitleFont( const sf::Font& font );
	void SetSize( const Vec2f& size );
	void SetPosition( const Vec2f& relPos );
	void SetScreenSize( const Vec2f& size );
	void SetFlag( const flag_t flag, bool value );
	void Move( const Vec2f& offset );

	sf::FloatRect GetGlobalBounds() const;
	sf::FloatRect GetTitleBarBounds() const;
	bool GetFlag( flag_t flag ) const;
	// this is interesting 
	template<flag_t flag>
	bool GetFlag() const
	{
		return this->flags[flag];
	}

	void Update();

private:
	// 0.0 - 1.0, from top-left corner of the screen
	Vec2f relativePosition;
	Vec2f screenSize;
	Flags flags;
	bool textNeedUpdate = true;
	bool positionsNeedsUpdate = true;

	sf::RectangleShape backgroundRect;
	sf::RectangleShape titleRect;
	sf::Text titleText;
	std::string titleString;

	void updateText();
	void updatePositions();
	void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
};

}