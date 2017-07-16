/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics.hpp>
#include "gui/GUIWindow.hpp"
#include "gui/Color.hpp"

int main()
{
	sf::RenderWindow win( { 800,600 }, "" );
	sf::Event ev;
	sf::Font font;
	font.loadFromFile( "consolas.ttf" );
	con::GUIWindow guiWin( { 0.5f, 0.5f }, "Very long title! 1234567890" );
	guiWin.SetTitleFont( font );
	guiWin.SetSize( { 200, 300 } );
	guiWin.SetScreenSize( { 800,600 } );

	con::GUIWindow guiWin2( { 0.1f, 0.3f }, "Short title" );
	guiWin2.SetTitleFont( font );
	guiWin2.SetSize( { 200, 100 } );
	guiWin2.SetScreenSize( { 800,600 } );

	while ( win.isOpen() ) {
		while ( win.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				win.close();
		}

		guiWin.Update();
		guiWin2.Update();

		win.clear();
		win.draw( guiWin );
		win.draw( guiWin2 );
		win.display();
	}

	return 0;
}