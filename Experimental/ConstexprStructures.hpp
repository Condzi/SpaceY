/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Config.hpp>

namespace con
{
	namespace experimental
	{
		// Replace with string_view if need more flexibility.
		// TODO: Add operator<<() for cout
		struct constexprString_t final
		{
			cstr_t data;
			uint16_t size;

			template <uint16_t N>
			constexpr constexprString_t( const char( &s )[N] ) :
				data( s ),
				size( N - 1 )
			{}

			constexprString_t() = delete;
		};		
	}
}