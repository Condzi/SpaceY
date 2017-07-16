/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <cinttypes>

#include <Core/Macros.hpp>
#include <Core/Config.hpp>

// IDEA: Figure out how to disable or fix E0904, E0493 errors

namespace con {
namespace internal {

	// TODO: Change enable_if to if constexpr, maybe make To<> constexpr?
	template <typename From>
	std::enable_if_t<std::is_integral_v<From>, std::string>
		inline ToStr( const From& src )
	{
		return ( std::_Integral_to_string<char>( +src ) );
	}

	template <typename From>
	std::enable_if_t<std::is_floating_point_v<From>, std::string>
		inline ToStr( const From& src )
	{
		return ( std::_Floating_to_string( "%f", src ) );
	}
}

// If cast to string
template <typename To_, typename From>
std::enable_if_t<std::is_same_v<std::string, To_>, To_>
inline To( const From& src )
{
	return internal::ToStr<From>( src );
}

// If not cast to string
template <typename To_, typename From>
std::enable_if_t<!std::is_same_v<std::string, To_>, To_>
inline To( const From& src )
{
	return static_cast<To_>( src );
}

template <typename To_, typename From>
inline To_ To( From* src )
{
	CON_STATIC_ASSERT( false, "this cast is not available" );
}

template<>
inline int8_t To<int8_t, std::string>( const std::string& src )
{
	// No function that converts to char.
	return To<int8_t>( std::stoi( src ) );
}

template<>
inline uint8_t To<uint8_t, std::string>( const std::string& src )
{
	// No function that converts to unsigned char.
	return To<uint8_t>( std::stoull( src ) );
}

template<>
inline int16_t To<int16_t, std::string>( const std::string& src )
{
	// No function that converts to short.
	return To<int16_t>( std::stoi( src ) );
}

template<>
inline uint16_t To<uint16_t, std::string>( const std::string& src )
{
	// No function that converts to unsigned short or unsigned int.
	return To<uint16_t>( std::stoull( src ) );
}

template<>
inline int32_t To<int32_t, std::string>( const std::string& src )
{
	return std::stoi( src );
}

template<>
inline uint32_t To<uint32_t, std::string>( const std::string& src )
{
	// No function that converts to unsigned int.
	return To<uint32_t>( std::stoull( src ) );
}

template<>
inline int64_t To<int64_t, std::string>( const std::string& src )
{
	return std::stoll( src );
}

template<>
inline uint64_t To<uint64_t, std::string>( const std::string& src )
{
	return std::stoull( src );
}

template<>
inline float To<float, std::string>( const std::string& src )
{
	return std::stof( src );
}

template<>
inline double To<double, std::string>( const std::string& src )
{
	return std::stod( src );
}

template<>
inline bool To<bool, std::string>( const std::string& src )
{
	std::string copy = src;
	std::transform( copy.begin(), copy.end(), copy.begin(), ::tolower );

	if ( copy == "false" || copy == "0" )
		return false;

	return true;
}

// const char* alternatives 

template<>
inline int8_t To<int8_t, const char>( cstr_t src )
{
	return To<int8_t>( std::string( src ) );
}

template<>
inline uint8_t To<uint8_t, const char>( cstr_t src )
{
	return To<uint8_t>( std::string( src ) );
}

template<>
inline uint16_t To<uint16_t, const char>( cstr_t src )
{
	return To<uint16_t>( std::string( src ) );
}

template<>
inline int32_t To<int32_t, const char>( cstr_t src )
{
	return To<int32_t>( std::string( src ) );
}

template<>
inline uint32_t To<uint32_t, const char>( cstr_t src )
{
	return To<uint32_t>( std::string( src ) );
}

template<>
inline int64_t To<int64_t, const char>( cstr_t src )
{
	return To<int64_t>( std::string( src ) );
}

template<>
inline uint64_t To<uint64_t, const char>( cstr_t src )
{
	return To<uint64_t>( std::string( src ) );
}

template<>
inline float To<float, const char>( cstr_t src )
{
	return To<float>( std::string( src ) );
}

template<>
inline double To<double, const char>( cstr_t src )
{
	return To<double>( std::string( src ) );
}

template<>
inline bool To<bool, const char>( cstr_t src )
{
	return To<bool>( std::string( src ) );
}
}