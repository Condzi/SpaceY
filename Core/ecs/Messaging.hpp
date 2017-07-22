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

namespace con {
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
	Message<T>* AddMessage( messageID_t id, const T& data );
	template <typename T>
	Message<T>* GetUniqueMessage( messageID_t id );
	template <typename T>
	std::vector<Message<T>*> GetAllMessages( const messageID_t id );

	void ClearMessages();

private:
	std::vector<std::unique_ptr<internal::messageInterface_t>> messages;

	std::vector<std::unique_ptr<internal::messageInterface_t>>::const_iterator findMessage( messageID_t id ) const;
};

#include <Core/ecs/Messaging.inl>
}