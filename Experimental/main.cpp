/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>

#include "Settings.hpp"

using namespace con::experimental;

int main()
{
	for ( auto& record : DefaultSettings<SETTINGS_DEFAULT_ENGINE>::records )
		std::cout << '[' << record.section.data << "] " << record.name.data << " = " << record.value.data << '\n';

	std::cin.get();
}