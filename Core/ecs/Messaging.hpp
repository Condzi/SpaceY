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
			bool safeDelete = false;
			messageID_t id = 0;
			const size_t uniqueID;

			messageInterface_t( messageID_t _id, size_t _uniqueID ) :
				id( std::move( _id ) ), uniqueID( std::move( _uniqueID ) )
			{}
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
	struct Message final :
		internal::messageInterface_t
	{
		T data;

		Message( messageID_t _id, T _data, size_t _uniqueID ) :
			messageInterface_t( std::move( _id ), std::move( _uniqueID ) ),
			data( std::move( _data ) )
		{}
	};

	/*
	===============================================================================
	Created by: Condzi
		Contains messages. GetMessage return temporary reference - it'll be invalid
		when safeDelete will be marked as true.

	===============================================================================
	*/
	class Messenger final
	{
	public:
		template <typename T>
		void AddMessage( const messageID_t id, const T& data )
		{
			this->messages.emplace_back( std::make_unique<Message<T>>( id, data, this->messages.size() ) );
		}
		template <typename T>
		Message<T>* GetUniqueMessage( const messageID_t id )
		{
			auto result = this->findMessage( id );
			if ( result != this->messages.end() )
				return reinterpret_cast<Message<T>*>( ( *result ).get() );

			return nullptr;
		}
		template <typename T>
		std::vector<Message<T>*> GetAllMessages( const messageID_t id )
		{
			std::vector<Message<T>*> vec;
			vec.reserve( this->messages.size() );

			for ( auto& message : this->messages )
				if ( message && message->id == id )
					vec.push_back( reinterpret_cast<Message<T>*>( ( message.get() ) ) );

			return vec;
		}

		void ClearMessages()
		{
			this->messages.erase( std::remove_if( this->messages.begin(), this->messages.end(), []( auto& msg )
			{
				return ( !msg ) || msg->safeDelete;
			} ), this->messages.end() );
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