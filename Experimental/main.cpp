/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>
#include <array>

#include "Settings.hpp"

using namespace con::experimental;

int main()
{
	Settings<SETTINGS_ENGINE> engineSettings;

	if ( !engineSettings.Load( "engine.ini" ) || !engineSettings.DoesMatchWithDefault())
		engineSettings.CreateDefault();

	std::cout<< *engineSettings.Get( "WINDOW", "TITLE" );

	std::cin.get();
}