/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/ecs/Messaging.hpp>

namespace con {

void Messenger::ClearMessages()
{
	this->messages.erase( std::remove_if( this->messages.begin(), this->messages.end(), []( auto& msg )
	{
		return ( !msg ) || msg->safeDelete;
	} ), this->messages.end() );
}

std::vector<std::unique_ptr<internal::messageInterface_t>>::const_iterator Messenger::findMessage( messageID_t id ) const
{
	return std::find_if( this->messages.begin(), this->messages.end(),
						 [id]( auto& ptr )
	{
		return ptr->id == id;
	} );
}
}