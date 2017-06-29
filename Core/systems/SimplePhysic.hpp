/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/EntityManager.hpp>
#include <Core/ecs/System.hpp>
#include <Core/ecs/Functions.hpp>
#include <Core/components/SimpleBody.hpp>
#include <Core/physic/Manifold.hpp>
// FRAME_TIME
#include <Core/time/Time.hpp>
// Context structure.
#include <Core/state/State.hpp>
#include <Core/Settings.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Updates velocity of Entities, detects collision.

	===============================================================================
	*/
	class SimplePhysicSystem final :
		public System
	{

	public:
		SimplePhysicSystem( Context cont ) :
			System( std::move( cont ) )
		{}

		systemID_t GetID() const override
		{
			return 1;
		}

		void Init() override
		{
			this->signature = createComponentSignature( getComponentTypeID<SimpleBodyComponent>() );
			this->ups = asSeconds( 1.0f / static_cast<uint8_t>( this->context.settings->GetInt( "PHYSIC", "UPS" ) ) );
		}

		void Update() override;

	private:
		const Vec2f GRAVITY { 0, 10 };
		componentBitset_t signature;
		std::vector<SimpleBodyComponent*> bodies;
		std::vector<Manifold> manifolds;

		Time timeAccumulator;
		Time ups;

		void updatePhysic();
		void setBodies();
		void integrateForces();
		void clearForces();
		void integrateVelocity();
	};
}