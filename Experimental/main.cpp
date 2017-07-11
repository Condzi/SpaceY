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
	std::cout << DefaultSettings<SETTINGS_DEFAULT_ENGINE>::Get( "WINDOW", "FPS" );

	std::cin.get();
}