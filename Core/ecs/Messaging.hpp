/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <algorithm>
#include <cinttypes>
#include <memory>
#include <vector>

#include <Core/ecs/Config.hpp>

namespace con
{
	namespace internal
	{
		struct messageInterface_t
		{
			messageID_t id = 0;
			const size_t uniqueID;
			virtual ~messageInterface_t() {}
		};
	}

	/*
	===============================================================================
	Created by: Condzi
		Non-inheritable struct that contains message id and data of type T. It
		also contains constant uniqueID to distinguish messages (unique for current
		frame).

	===============================================================================
	*/
	template <typename T>
	struct message_t final :
		internal::messageInterface_t
	{
		T data;

		message_t( messageID_t _id, T _data, size_t _uniqueID ) :
			id( _id ), data( std::move( _data ) ),
			uniqueID( std::move( _uniqueID ) )
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
			this->messages.emplace_back( std::make_unique<message_t<T>>( id, data, this->messages.size() ) );
		}
		template <typename T>
		message_t<T>& GetUniqueMessage( const messageID_t id )
		{
			auto result = this->findMessage( id );
			if ( result != this->messages.end() )
				return static_cast<message_t<T>&>( ( *result ).get() );
		}
		template <typename T>
		std::vector<message_t<T>*> GetAllMessages( const messageID_t id )
		{
			std::vector<message_t<T>*> vec;
			vec.reserve( this->messages.size() );

			for ( auto& message : this->messages )
				if ( message->id == id )
					vec.push_back( static_cast<message_t<T>*>( ( *result ).get() ) );

			return vec;
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