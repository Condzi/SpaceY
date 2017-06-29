/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/System.hpp>
#include <Core/ecs/Functions.hpp>
#include <Core/ecs/EntityManager.hpp>
#include <Core/components/Position.hpp>
#include <Core/components/Drawable.hpp>
#include <Core/components/SimpleBody.hpp>
#include <Core/state/State.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Sets position of PositionComponent and DrawableComponent to match
		SimpleBody position.

	===============================================================================
	*/
	class PositionUpdateSystem final :
		public System
	{
	public:
		PositionUpdateSystem( Context cont ) :
			System( std::move( cont ) )
		{}

		systemID_t GetID() const override
		{
			return 0;
		}

		void Init() override
		{
			this->signature = createComponentSignature( getComponentTypeID<PositionComponent>() );
		}

		void Update() override
		{
			auto entities = this->context.entityManager->GetEntitiesWithSignature( this->signature );
			entities.erase( std::remove_if( std::begin( entities ), std::end( entities ),
				[]( auto entity )
			{
				return !entity->IsActive() || !entity->IsAlive();
			} ), std::end( entities ) );

			for ( auto entity : entities )
			{
				PositionComponent* position = &entity->GetComponent<PositionComponent>();
				DrawableComponent* drawable = nullptr;
				SimpleBodyComponent* body = nullptr;

				if ( entity->HasComponent<DrawableComponent>() )
					drawable = &entity->GetComponent<DrawableComponent>();
				if ( entity->HasComponent<SimpleBodyComponent>() )
					body = &entity->GetComponent<SimpleBodyComponent>();

				if ( body )
				{
					position->x = body->position.x;
					position->y = body->position.y;
				}
				if ( drawable )
					drawable->sprite.setPosition( position->x, position->y );
			}
		}

	private:
		componentBitset_t signature;
	};
}