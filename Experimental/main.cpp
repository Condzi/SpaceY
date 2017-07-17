/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics.hpp>
#include "gui/GUIWindow.hpp"
#include "gui/GUIButton.hpp"

#include <Core/logger/Logger.hpp>

using con::Logger;

int main()
{
	sf::RenderWindow win( { 800,600 }, "" );
	win.setFramerateLimit( 60 );
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

	guiWin.SetFlag( con::GUIWindow::EXPANDED, true );
	LOG( guiWin.GetFlag<con::GUIWindow::EXPANDED>(), INFO, CONSOLE );
	guiWin2.SetFlag( con::GUIWindow::EXPANDED, true );
	guiWin2.SetFlag( con::GUIWindow::EXPANDED, true );
	
	con::GUIButton button( { 0.3,0.3 }, "Click me" );
	button.SetTextFont( font );
	button.SetSize( { 0,50 } );
	button.SetScreenSize( { 800,600 } );

	con::Vec2f prevMousePos( sf::Mouse::getPosition( win ) );

	while ( win.isOpen() ) {
		while ( win.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				win.close();
		}


		auto mousePos = con::Vec2f( sf::Mouse::getPosition( win ) );
		auto delta = mousePos - prevMousePos;
		prevMousePos = mousePos;
		if ( guiWin.GetTitleBarBounds().contains( mousePos.AsSFMLVec() ) &&
			 sf::Mouse::isButtonPressed( sf::Mouse::Left ) ) {
			con::Vec2f offset;
			offset.Set( delta.x ? 1/(800 / delta.x) : 0, delta.y ? 1/(600 / delta.y) : 0 );
			LOG( offset.AsString(), INFO, CONSOLE );
			if ( offset.x == 1 || offset.y == 1 )
				guiWin.Move( { 0,0 } );

			guiWin.Move( offset );
		}

		guiWin.Update();
		guiWin2.Update();
		button.Update();

		win.clear();
		win.draw( guiWin );
		win.draw( guiWin2 );
		win.draw( button );
		win.display();
	}

	return 0;
}