/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Config.hpp>

namespace con {

/*
===============================================================================
Created by: Condzi
	Compile time array. Used by constexprString_t.

===============================================================================
*/
template <typename T>
struct constexprArray_t final
{
	using storage_type = uint16_t;
	using data_type = T;

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

/*
===============================================================================
Created by: Condzi
	Finds something in interval of poitners using tester lambda.

===============================================================================
*/
template <typename It, typename Lambda>
constexpr It constexprFindIf( const It& b, const It& e, const Lambda& tester )
{
	auto begin = b;
	while ( begin != e ) {
		if ( tester( *begin ) )
			break;

		++begin;
	}

	return begin;
}

/*
===============================================================================
Created by: Condzi
	Three constexprString_t values used by Settings class.

===============================================================================
*/
struct constexprRecord_t final // compile time version of INIFile::record_t
{
	constexprString_t section, name, value;
	// Default constructor is needed to initialize empty Settings.
	constexpr constexprRecord_t( constexprString_t _section = "", constexprString_t _name = "", constexprString_t _value = "" ) :
		section( std::move( _section ) ),
		name( std::move( _name ) ),
		value( std::move( _value ) )
	{}

	const bool SkipWhenSaving() const
	{
		return this->section.size == 0 || this->name.size == 0 || this->value.size == 0;
	}

	constexpr bool operator==( const constexprRecord_t& second ) const
	{
		return ( this->section == second.section ) && ( this->name == second.name );
	}
};
}