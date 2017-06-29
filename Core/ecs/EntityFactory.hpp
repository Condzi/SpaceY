/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Entity.hpp>
#include <Core/ecs/Config.hpp>
#include <Core/Assert.hpp>

namespace con
{
	// Forward declaration.
	struct Context;

	struct EntityCreator
	{
		virtual ~EntityCreator() {}

		virtual entityID_t GetID() const = 0;
		virtual void CreateEntity( Entity& entity, Context& context ) = 0;
	};

	/*
	===============================================================================
	Created by: Condzi
		Stores Entity Creators. Add Creators in LoadingState, before calling PlayState.

	===============================================================================
	*/
	class EntityFactory final
	{
	public:
		template <typename T>
		void AddCreator()
		{
			CON_STATIC_ASSERT( std::is_base_of_v<EntityCreator, T>, "T must inherit from EntityCreator" );
			auto creator = std::make_unique<T>();

			auto result = std::find_if( std::begin( this->creators ), std::end( this->creators ),
				[&creator]( auto& creatorB )
			{
				return creator->GetID() == creatorB->GetID();
			} );
			if ( result != std::end( this->creators ) )
			{
				LOG( "Factory of id " << +creator->GetID() << " is already in EntityFactory", WARNING, BOTH );
				return;
			}

			this->creators.emplace_back( std::move( creator ) );
		}

		Entity& CreateEntity( Entity& src, const entityID_t id, Context& context )
		{
			auto result = std::find_if( std::begin( this->creators ), std::end( this->creators ),
				[id]( auto& creator )
			{
				return id == creator->GetID();
			} );

			if ( result == std::end( this->creators ) )
				LOG( "Cannot find EntityCreator for id " << +id, ERROR, BOTH );
			else
				( *result )->CreateEntity( src, context );

			return src;
		}

	private:
		std::vector<std::unique_ptr<EntityCreator>> creators;
	};
}