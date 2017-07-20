/*
Conrad 'Condzi' Kubacki 2017
https://github.com/condzi
*/

#pragma once

#include <algorithm>
#include <type_traits>
#include <string>
#include <cinttypes>
#include <cctype>

#include <Core/Macros.hpp>
#include <Core/Config.hpp>

namespace con {
namespace experimental {

template <typename TypeA, typename TypeB>
constexpr bool IsSameType = std::is_same<TypeA, TypeB>::value;

template <typename To_, typename From>
inline To_ To( From src );

namespace internal {

	template <typename From>
	inline std::string ToStr( const From& src )
	{
		if constexpr ( IsSameType<bool, From> )
			return src != 0;
		else if constexpr ( std::is_integral_v<From> )
			return ( std::_Integral_to_string<char>( +src ) );
		else if constexpr (std::is_floating_point_v<From> )
			return ( std::_Floating_to_string( "%f", src ) );
		else	
			CON_STATIC_ASSERT(false, "invalid to string conversion parameters")
	}

	inline std::string ToLower( std::string str )
	{
		std::transform( str.begin(), str.end(), str.begin(),
						[]( unsigned char c )
		{
			return std::tolower( c );
		} );
		return str;
	}

	template <typename To_>
	inline To_ FromStr( const std::string& src )
	{
		if constexpr ( IsSameType<int8_t, To_> )
			return To<int8_t>( std::stoi( src ) );
		else if constexpr ( IsSameType<uint8_t, To_> )
			return To<uint8_t>( std::stoull( src ) );
		else if ( IsSameType<int16_t, To_> )
			return To<int16_t>( std::stoi( src ) );
		else if constexpr( IsSameType<uint16_t, To_> )
			return To<uint16_t>( std::stoull( src ) );
		else if constexpr( IsSameType<int32_t, To_> )
			return std::stoi( src );
		else if constexpr( IsSameType<uint32_t, To_> )
			return To<uint32_t>( std::stoull( src ) );
		else if constexpr( IsSameType<int64_t, To_> )
			return std::stoll( src );
		else if constexpr( IsSameType<uint64_t, To_> )
			return std::stoull( src );
		else if constexpr( IsSameType<float, To_> )
			return std::stof( src );
		else if constexpr( IsSameType<double, To_> )
			return std::stod( src );
		else if constexpr( IsSameType<bool, To_> )
			return !( ToLower( src ) == "false" || ToLower( src ) == "0" );
		else
			CON_STATIC_ASSERT( false, "invalid from string conversion parameter" );
	}
}

template <typename To_, typename From>
inline To_ To( From src )
{
	//if constexpr ( IsSameType<void, To_> ||
	//			   IsSameType<void, From> )
	//	CON_STATIC_ASSERT( false, "invalid conversion argument <void>" );

	if constexpr( IsSameType<cstr_t, From> ||
				  IsSameType<std::string, From> )
		return internal::FromStr<To_>( std::string( src ) );
	else if constexpr ( IsSameType<std::string, To_> )
		return internal::ToStr( src );
	else
		return static_cast<To_>( src );
}

}
}