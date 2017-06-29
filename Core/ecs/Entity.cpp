/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/ecs/EntityManager.hpp>

namespace con
{
	void Entity::AddGroup( const groupID_t group )
	{
		this->groupBitset[group] = true;
		this->entityManager->AddToGroup( this, group );
	}
}