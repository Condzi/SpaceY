/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>

#include "INIFile.hpp"

int main()
{
	con::experimental::INIFile file;
	file.Open( "test.ini" );
	file.Parse();

	std::cout << file.GetValue( "SECTION", "val1" ) << '\n';
	std::cout << file.GetValue( "SECTION", "val2" ) << '\n';
	file.AddValue( "TEST SECTION", "val3", "hello world once more" );
	file.Save();
	std::cin.get();
	return 0;
}