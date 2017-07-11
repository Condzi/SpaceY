/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Config.hpp>

namespace con {
namespace experimental {
// TODO: Add comments.
template <typename T>
struct constexprArray_t final
{
	typedef uint16_t storage_type;
	typedef T data_type;

	const data_type* data;
	storage_type size;

	template <storage_type N>
	constexpr constexprArray_t( const T( &d )[N] ) :
		data( d ),
		size( N - 1 )
	{}

	constexpr const data_type& operator[] ( const storage_type i ) const
	{
		return this->data[i];
	}

	constexpr bool operator==( const constexprArray_t<data_type>& second ) const
	{
		if ( this->size != second.size )
			return false;

		for ( storage_type i = 0; i < this->size; i++ )
			if ( this->data[i] != second.data[i] )
				return false;
		return true;
	}
};

// Replace with string_view if need more flexibility.
using constexprString_t = constexprArray_t<const char>;
inline std::ostream& operator<<( std::ostream& stream, const constexprString_t& str )
{
	return stream << str.data;
}

// TODO: Add comments.
template <typename It, typename Lambda>
constexpr It constexprFindIf( const It& b, const It& e, Lambda tester )
{
	auto begin = b;
	while ( begin != e ) {
		if ( tester( *begin ) )
			break;

		++begin;
	}

	return begin;
}

// TODO: Add comments.
struct constexprRecord_t final // compile time version of INIFile::record_t
{
	constexprString_t section, name, value;
	// Default constructor is needed to initialize empty Settings.
	constexpr constexprRecord_t( constexprString_t _section = "", constexprString_t _name = "", constexprString_t _value = "" ) :
		section( std::move( _section ) ),
		name( std::move( _name ) ),
		value( std::move( _value ) )
	{}

	constexpr bool operator==( const constexprRecord_t& second ) const
	{
		return ( this->section == second.section ) && ( this->name == second.name );
	}
};
}
}