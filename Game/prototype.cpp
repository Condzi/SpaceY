/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics.hpp>

sf::Font font;
sf::RenderWindow window;
sf::Event event;

void init();
void pollEvent();
void update();
void draw();

int main()
{
	init();

	while ( window.isOpen() )
	{
		pollEvent();
		update();
		draw();
	}

	return 0;
}

void init()
{
	window.create( { 800,600 }, "" );

	font.loadFromFile( "consolas.ttf" );
}

void pollEvent()
{
	while ( window.pollEvent( event ) )
		if ( event.type == sf::Event::Closed )
			window.close();
}

void update()
{

}

void draw()
{
	window.clear();
	window.display();
}
