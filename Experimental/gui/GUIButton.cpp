#include <SFML/Graphics/RenderWindow.hpp>

#include "Functions.hpp"
#include "GUIButton.hpp"
/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

namespace con {

GUIButton::GUIButton( Vec2f relPos, std::string title ) :
	relativePosition( std::move( relPos ) )
{
	text.setString( title );

	// TODO: Add this values to default engine settings in UI section
	this->shape.setFillColor( { 37,37,37 } );
	this->text.setFillColor( { 241, 241, 241 } );
}

void GUIButton::SetText( const std::string& title )
{
	this->text.setString( title );
	this->textNeedUpdate = true;
}

void GUIButton::SetTextFont( const sf::Font& font )
{
	this->text.setFont( font );
	this->textNeedUpdate = true;
}

void GUIButton::SetSize( const Vec2f& size )
{
	this->shape.setSize( size.AsSFMLVec() );
	this->positionsNeedsUpdate = true;
}

void GUIButton::SetPosition( const Vec2f& relPos )
{
	this->relativePosition = relPos;
	this->positionsNeedsUpdate = true;
}

void GUIButton::SetScreenSize( const Vec2f& size )
{
	this->screenSize = size;
	this->positionsNeedsUpdate = true;
}

void GUIButton::SetFlag( const flag_t flag, bool value )
{
	this->flags[flag] = value;
}

void GUIButton::Move( const Vec2f& offset )
{
	this->relativePosition += offset;
	this->positionsNeedsUpdate = true;
}

sf::FloatRect GUIButton::GetGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void GUIButton::Update()
{
	if ( this->textNeedUpdate )
		this->updateText();
	if ( this->positionsNeedsUpdate )
		this->updatePositions();
}

void GUIButton::updateText()
{
	// Todo: experiment with 'fit' arg
	auto newTextSize = findBestTextSize(
		*this->text.getFont(), this->shape.getGlobalBounds().height );

	this->text.setCharacterSize( newTextSize );
	this->textNeedUpdate = false;

	this->shape.setSize( { getCorrectTextBounds( this->text ).x,
							this->shape.getGlobalBounds().height } );
}

void GUIButton::updatePositions()
{
	Vec2f realPosition = screenSize * relativePosition;

	this->shape.setPosition( realPosition.AsSFMLVec() );
	this->text.setPosition( realPosition.AsSFMLVec() );

	this->positionsNeedsUpdate = false;
}

void GUIButton::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( this->shape, states );
	target.draw( this->text, states );
}
}