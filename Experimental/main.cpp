/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>
#include <array>

#include "Settings.hpp"
#include "Parser.hpp"

using namespace con::experimental;

// This settings can be defined _anywhere_. I think.
template <>
struct Settings<SETTINGS_DEFAULT_GAME> final
{
	BEGIN_SETTINGS_DEF

		DEFINE_SETTING( "PLAYER", "POSITION_X", "100" ),
		DEFINE_SETTING( "PLAYER", "POSITION_Y", "200" )

		END_SETTINGS_DEF
};

int main()
{
	Settings<SETTINGS_GAME> engineSettings;

	if ( !engineSettings.Load( "game.ini" ) || !engineSettings.DoesMatchWithDefault() )
		engineSettings.CreateDefault();

	//*engineSettings.Get( "PLAYER", "POSITION_X" ) = parser::valToStr( 512 );
	std::cout << *engineSettings.Get( "PLAYER", "POSITION_X" );
	engineSettings.SaveCurrent();
	std::cin.get();
}