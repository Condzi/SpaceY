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
		template <typename T>
		struct constexprArray_t final
		{
			const T* data;
			uint16_t size;

			template <uint16_t N>
			constexpr constexprArray_t( const T( &d )[N] ) :
				data( d ),
				size( N - 1 )
			{}

			constexpr const T& operator[] ( const uint16_t i ) const
			{
				return this->data[i];
			}

			constexpr bool operator==( const constexprArray_t<T> second ) const
			{
				if ( this->size != second.size )
					return false;

				for ( uint16_t i = 0; i < this->size; i++ )
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

		template <typename It, typename Lambda>
		constexpr It constexprFindIf( const It& b, const It& e, Lambda tester )
		{
			auto begin = b;
			while ( begin != e )
			{
				if ( tester( *begin ) )
					break;

				++begin;
			}

			return begin;
		}

		struct record_t final // compile time version of INIFile::record_t
		{
			constexprString_t section, name, value;
			// Default constructor is needed to initialize empty Settings.
			constexpr record_t( constexprString_t _section = "", constexprString_t _name = "", constexprString_t _value = "" ) :
				section( std::move( _section ) ),
				name( std::move( _name ) ),
				value( std::move( _value ) )
			{}

			constexpr bool operator==( const record_t& second ) const
			{
				return ( this->section == second.section ) && ( this->name == second.name );
			}
		};
	}
}