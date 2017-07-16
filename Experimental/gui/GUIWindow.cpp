/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics/RenderWindow.hpp>

#include "GUIWindow.hpp"
#include "Functions.hpp"

namespace con {

GUIWindow::GUIWindow( Vec2f relPos, std::string title ) :
	relativePosition( std::move( relPos ) ),
	titleString( std::move( title ) )
{
	this->titleText.setCharacterSize( SIZE_TITLEBAR_CHARACTER_SIZE );
	this->titleRect.setSize( { 0, SIZE_TITLEBAR_Y } );

	// TODO: Add this values to default engine settings in UI section
	this->titleRect.setFillColor( { 79, 39, 129 } );
	this->backgroundRect.setFillColor( { 37,37,37 } );
	this->titleText.setFillColor( { 241, 241, 241 } );
}

void GUIWindow::SetTitleText( const std::string& text )
{
	this->titleString = text;
	this->titleText.setString( text );
	this->textNeedUpdate = true;
}

void GUIWindow::SetTitleFont( const sf::Font& font )
{
	this->titleText.setFont( font );
	this->textNeedUpdate = true;
}

void GUIWindow::SetSize( const Vec2f& size )
{
	this->backgroundRect.setSize( { size.x, size.y + SIZE_TITLEBAR_Y } );
	this->titleRect.setSize( { size.x, SIZE_TITLEBAR_Y } );
	this->textNeedUpdate = true;
}

void GUIWindow::SetPosition( const Vec2f& relPos )
{
	this->relativePosition = relPos;
	this->positionsNeedsUpdate = true;
}

void GUIWindow::SetScreenSize( const Vec2f& size )
{
	this->screenSize = size;
	this->positionsNeedsUpdate = true;
}

void GUIWindow::SetFlag( const flag_t flag, bool value )
{
	this->flags[flag] = value;
}

void GUIWindow::Move( const Vec2f& offset )
{
	this->relativePosition += offset;
	this->positionsNeedsUpdate = true;
}

void GUIWindow::Update()
{
	if ( this->textNeedUpdate )
		this->updateText();
	if ( this->positionsNeedsUpdate )
		this->updatePositions();
}

void GUIWindow::updateText()
{
	this->titleText.setString( this->titleString );
	auto textBounds = getCorrectTextBounds( this->titleText );
	auto charWidth = this->titleText.getFont()->getGlyph( 'g', SIZE_TITLEBAR_CHARACTER_SIZE, false ).bounds.width;
	Vec2f rectBounds = { this->titleRect.getGlobalBounds().width, this->titleRect.getGlobalBounds().height };
	// TODO: do better code here

	float difference = textBounds.x - rectBounds.x;
	auto charsToRemove = difference > 0 ? To<uint8_t>( difference / charWidth + 1 ) + 3 : 0; // 3 for '...'

	std::string newStr( this->titleString.c_str(), this->titleString.size() - charsToRemove );
	if ( charsToRemove )
		newStr += "...";

	this->titleText.setString( newStr );
	this->textNeedUpdate = false;
}

void GUIWindow::updatePositions()
{
	Vec2f realPosition = screenSize * relativePosition;

	this->backgroundRect.setPosition( realPosition.AsSFMLVec() );
	this->titleRect.setPosition( realPosition.AsSFMLVec() );
	this->titleText.setPosition( realPosition.AsSFMLVec() );

	this->positionsNeedsUpdate = false;
}

void GUIWindow::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	if ( this->flags[EXPANDED] )
		target.draw( this->backgroundRect, states );
	if ( this->flags[NO_TITLE_BAR] )
		return;

	target.draw( this->titleRect, states );
	target.draw( this->titleText, states );
}

}