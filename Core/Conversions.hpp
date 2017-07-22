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

namespace con {

template <typename TypeA, typename TypeB>
constexpr bool IsSameType = std::is_same<TypeA, TypeB>::value;

template <typename TO, typename From>
inline TO To( const From& src );

namespace internal {
	template <typename From>
	inline std::string ToStr( const From& src )
	{
		if constexpr ( IsSameType<bool, From> )
			return src != 0 ? "true" : "false";
		else if constexpr ( std::is_integral_v<From> || std::is_floating_point_v<From> )
			return std::to_string( +src );
		else
			CON_STATIC_ASSERT( false, "invalid to string conversion parameters" );
	}

	inline std::string ToLower( std::string str )
	{
		std::transform( str.begin(), str.end(), str.begin(), ::tolower );
		return str;
	}

	template <typename TO>
	inline TO FromStr( const std::string& src )
	{
		if constexpr ( IsSameType<int8_t, TO> )
			return To<int8_t>( std::stoi( src ) );
		else if constexpr ( IsSameType<uint8_t, TO> )
			return To<uint8_t>( std::stoull( src ) );
		else if constexpr ( IsSameType<int16_t, TO> )
			return To<int16_t>( std::stoi( src ) );
		else if constexpr ( IsSameType<uint16_t, TO> )
			return To<uint16_t>( std::stoull( src ) );
		else if constexpr ( IsSameType<int32_t, TO> )
			return std::stoi( src );
		else if constexpr ( IsSameType<uint32_t, TO> )
			return To<uint32_t>( std::stoull( src ) );
		else if constexpr ( IsSameType<int64_t, TO> )
			return std::stoll( src );
		else if constexpr ( IsSameType<uint64_t, TO> )
			return std::stoull( src );
		else if constexpr ( IsSameType<float, TO> )
			return std::stof( src );
		else if constexpr ( IsSameType<double, TO> )
			return std::stod( src );
		else if constexpr ( IsSameType<bool, TO> )
			return !( ToLower( src ) == "false" || ToLower( src ) == "0" );
		else
			CON_STATIC_ASSERT( false, "invalid from string conversion parameter" );
	}
}

template <typename TO, typename From>
inline TO To( const From& src )
{
	if constexpr ( IsSameType<void, TO> ||
				   IsSameType<void, From> )
		CON_STATIC_ASSERT( false, "invalid conversion argument <void>" );

	if constexpr( IsSameType<std::string, From> )
		return internal::FromStr<TO>( std::string( src ) );
	else if constexpr ( IsSameType<std::string, TO> )
		return internal::ToStr( src );
	else
		return static_cast<TO>( src );
}

template <typename TO, typename From>
inline TO To( From* src )
{
	if constexpr ( IsSameType<const char, From> )
		return internal::FromStr<TO>( std::string( src ) );
	else
		CON_STATIC_ASSERT( false, "invalid conversion argument <poitner>" );
}
}