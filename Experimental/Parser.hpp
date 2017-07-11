/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <string>
#include <cinttypes>

#include <Core/Assert.hpp>

namespace con {
namespace experimental {
namespace parser {
template <typename T>
inline std::string valToStr( const T& val )
{
	return std::to_string( val );
}

template <typename T>
inline T strToVal( const std::string& src )
{
	CON_STATIC_ASSERT( false, "invalid string parsing type" );
}

template<>
inline int16_t strToVal( const std::string& src )
{
	// No function that converts to short.
	return static_cast<int16_t>( std::stoi( src ) );
}

template<>
inline uint16_t strToVal( const std::string& src )
{
	// No function that converts to unsigned short or unsigned int.
	return static_cast<uint16_t>( std::stoull( src ) );
}

template<>
inline int32_t strToVal( const std::string& src )
{
	return std::stoi( src );
}

template<>
inline uint32_t strToVal( const std::string& src )
{
	// No function that converts to unsigned int.
	return static_cast<uint32_t>( std::stoull( src ) );
}

template<>
inline int64_t strToVal( const std::string& src )
{
	return std::stoll( src );
}

template<>
inline uint64_t strToVal( const std::string& src )
{
	return std::stoull( src );
}

template<>
inline float strToVal( const std::string& src )
{
	return std::stof( src );
}

template<>
inline double strToVal( const std::string& src )
{
	return std::stod( src );
}
}
}
}