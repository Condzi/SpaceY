/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <algorithm>
#include <cinttypes>
#include <memory>
#include <vector>

namespace con
{
	using messageID_t = int8_t;

	namespace internal
	{
		struct messageInterface_t
		{
			messageID_t id = 0;
			virtual ~messageInterface_t() {}
		};
	}

	/*
	===============================================================================
	Created by: Condzi
		Non-inheritable struct that contains message id and data of type T.

	===============================================================================
	*/
	template <typename T>
	struct message_t final :
		internal::messageInterface_t
	{
		T data;

		message_t( messageID_t _id, T _data ) :
			id( _id ), data( std::move( _data ) )
		{}
	};

	/*
	===============================================================================
	Created by: Condzi
		Contains messages. GetMessage return temporary reference - it'll be invalid
		at next update, so don't store it - copy it's message_t::data.

	===============================================================================
	*/
	class Messenger final
	{
	public:
		template <typename T>
		void AddMessage( const messageID_t id, const T& data )
		{
			this->messages.emplace_back( std::make_unique<message_t<T>>( id, data ) );
		}
		template <typename T>
		message_t<T>& GetMessage( const messageID_t id )
		{
			auto result = this->findMessage( id );
			if ( result != this->messages.end() )
				return static_cast<message_t<T>&>( ( *result ).get() );
		}
		void ClearMessages()
		{
			this->messages.clear();
		}

	private:
		std::vector<std::unique_ptr<internal::messageInterface_t>> messages;

		auto findMessage( const messageID_t id ) const
		{
			return std::find_if( this->messages.begin(), this->messages.end(),
				[id]( auto& ptr )
			{
				return ptr->id == id;
			} );
		}
	};
}