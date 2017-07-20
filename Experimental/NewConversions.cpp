/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>
#include "Conversions.hpp"

using namespace con::experimental;

int main()
{
	auto str = "123";
	std::cout << std::boolalpha;
	//std::cout << IsSameType<decltype( str ), con::cstr_t>;
	std::cout << To<uint32_t>( "123" );

	std::cin.get();
}