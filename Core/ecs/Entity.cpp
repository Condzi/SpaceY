/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/ecs/EntityManager.hpp>

namespace con {

Entity::Entity( EntityManager& manager ) :
	entityManager( &manager )
{}

bool Entity::IsAlive() const
{
	return this->alive;
}

bool Entity::IsActive() const
{
	return this->active;
}

const componentBitset_t& Entity::GetComponentBitset() const
{
	return this->componentBitset;
}

void Entity::Kill()
{
	if ( this->HasComponent<ScriptComponent>() )
		this->GetComponent<ScriptComponent>().OnKill();

	this->alive = false;
}

void Entity::SetActive( bool val )
{
	if ( val != this->active )
		if ( !val ) {
			if ( this->HasComponent<ScriptComponent>() )
				this->GetComponent<ScriptComponent>().OnSleep();
			else
				if ( this->HasComponent<ScriptComponent>() )
					this->GetComponent<ScriptComponent>().OnActive();
		}

	this->active = val;
}

bool Entity::HasGroup( const groupID_t group ) const
{
	return this->groupBitset[group];
}

void Entity::AddGroup( const groupID_t group )
{
	this->groupBitset[group] = true;
	this->entityManager->AddToGroup( this, group );
}

void Entity::RemoveGroup( const groupID_t group )
{
	this->groupBitset[group] = false;
}
}