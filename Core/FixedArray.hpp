/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>

namespace con
{	
	/*
	===============================================================================
	Created by: Condzi
		Simple, fixed size array allocated on heap.

	===============================================================================
	*/
	template <typename T, size_t Size>
	class FixedArray
	{
	public:
		FixedArray() :
			size( Size ),
			data( new T[Size] )
		{}
		virtual ~FixedArray() {}

		const size_t GetSize() const
		{
			return this->size;
		}

		void Fill( const T& src )
		{
			for ( size_t i = 0; i < this->size; i++ )
				this->data[i] = src;
		}

		bool IsValidIndex( const size_t index ) const
		{
			return index < this->size;
		}

		T& At( const size_t index ) const
		{
			return ( *this )[index];
		}

		T& operator[]( const size_t index ) const
		{
			return this->data[index];
		}

	private:
		size_t size;
		std::unique_ptr<T[]> data;
	};
}