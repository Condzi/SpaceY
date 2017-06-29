/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Entity.hpp>
#include <Core/FixedArray.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Manages Entities. Every killed entity is updated at the end of the game loop.

	===============================================================================
	*/
	class EntityManager final
	{
	public:
		Entity& CreateEntity()
		{
			auto ptr = std::make_unique<Entity>( *this );
			Entity* raw = ptr.get();
			this->entities.emplace_back( std::move( ptr ) );
			return *raw;
		}

		std::vector<Entity*> GetEntitiesWithSignature( const componentBitset_t& bitset )
		{
			std::vector<Entity*> vec;
			for ( auto& entity : entities )
				if ( ( bitset & entity->GetComponentBitset() ) == bitset )
					vec.emplace_back( entity.get() );

			return vec;
		}

		std::vector<Entity*>& GetEntitiesByGroup( const groupID_t group )
		{
			return this->groupedEntities[group];
		}

		void AddToGroup( Entity* entity, const groupID_t group )
		{
			this->groupedEntities[group].emplace_back( entity );
		}

		void Refresh()
		{
			for ( groupID_t i = 0; i < MAX_GROUPS; i++ )
			{
				auto& vec = this->groupedEntities[i];

				vec.erase( std::remove_if( std::begin( vec ), std::end( vec ),
					[i]( auto entity )
				{
					return !entity->IsAlive() || !entity->HasGroup( i );
				} ), std::end( vec ) );
			}

			this->entities.erase(
				std::remove_if( std::begin( entities ), std::end( entities ),
					[]( const auto& entity )
			{
				return !entity->IsAlive();
			} ), std::end( entities ) );
		}

	private:
		std::vector<std::unique_ptr<Entity>> entities;
		FixedArray<std::vector<Entity*>, MAX_GROUPS> groupedEntities;
	};
}