/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics/Text.hpp>

#include <Core/Config.hpp>

namespace con
{
	sf::FloatRect con::getRealTextBounds( const sf::Text& text )
	{
		return sf::FloatRect(
			text.getPosition().x + ( text.getCharacterSize() * 3 ) / 50.0f,
			text.getPosition().y + ( text.getCharacterSize() * 15.3f ) / 50.0f,
			text.getGlobalBounds().width,
			text.getGlobalBounds().height
		);
	}
}
