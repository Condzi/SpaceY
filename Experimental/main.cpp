/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics.hpp>
#include "gui/Functions.hpp"


int main()
{
	sf::RenderWindow win( { 800,600 }, "" );
	sf::Event ev;
	sf::Font font;
	font.loadFromFile( "consolas.ttf" );
	sf::Text txt( "Hello, world!", font );
	sf::RectangleShape shape( con::getLocalSize( txt ) );
	txt.setPosition( 100, 100 );
	shape.setPosition( 100, 100 );
	shape.setFillColor( sf::Color::Red );

	while ( win.isOpen() ) {
		while ( win.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				win.close();
		}

		win.clear();
		win.draw( shape );
		win.draw( txt );
		win.display();
	}

	return 0;
}