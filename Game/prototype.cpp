/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics.hpp>

sf::Font font;
sf::RenderWindow window;
sf::Event event;

sf::Text sampleText;
sf::RectangleShape testRectangle;


void init();
void workInit();
void pollEvent();
void workUpdate();
void workDraw();
void draw();

int main()
{
	init();
	workInit();

	while ( window.isOpen() )
	{
		pollEvent();
		workUpdate();
		draw();
	}
}

void init()
{
	window.create( { 800,600 }, "" );

	font.loadFromFile( "consolas.ttf" );
}

void workInit()
{
	sampleText.setFont( font );
	sampleText.setString( "abc_ABC-321\nhello!\nWARNING?\nError?" );
	sampleText.setPosition( 100, 100 );
	sampleText.setFillColor( sf::Color::Red );
	sampleText.setCharacterSize( 100 );

	// magic offset ??
	testRectangle.setPosition( sampleText.getPosition().x, sampleText.getPosition().y + ( sampleText.getCharacterSize() * 15.3f ) / 50.0f );
	//testRectangle.setSize( GetLocalSize( sampleText ) );
	testRectangle.setSize( { sampleText.getGlobalBounds().width, sampleText.getGlobalBounds().height } );
}

void pollEvent()
{
	while ( window.pollEvent( event ) )
		if ( event.type == sf::Event::Closed )
			window.close();
}

void workUpdate()
{

}

void workDraw()
{
	window.draw( testRectangle );
	window.draw( sampleText );
}

void draw()
{
	window.clear();
	workDraw();
	window.display();
}
