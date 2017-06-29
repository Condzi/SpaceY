/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/systems/SimplePhysic.hpp>

namespace con
{
	void SimplePhysicSystem::Update()
	{
		this->timeAccumulator += Time::FRAME_TIME;

		if ( this->timeAccumulator >= this->ups )
		{
			this->setBodies();

			this->manifolds.clear();
			this->integrateForces();
			this->integrateVelocity();
			for ( auto bodyA : this->bodies )
				for ( auto bodyB : this->bodies )
				{
					if ( bodyA == bodyB )
						continue;

					Manifold manifold( bodyA, bodyB );
					if ( manifold.Check() )
						this->manifolds.emplace_back( manifold );
				}
		}

		while ( this->timeAccumulator >= this->ups )
		{
			this->updatePhysic();
			this->timeAccumulator -= this->ups;
		}
	}

	void SimplePhysicSystem::setBodies()
	{
		auto entities = this->context.entityManager->GetEntitiesWithSignature( this->signature );
		entities.erase( std::remove_if( std::begin( entities ), std::end( entities ),
			[]( auto entity )
		{
			return !entity->IsActive() || !entity->IsAlive();
		} ), std::end( entities ) );

		this->bodies.clear();
		for ( auto entity : entities )
			this->bodies.push_back( &entity->GetComponent<SimpleBodyComponent>() );
	}

	void SimplePhysicSystem::integrateForces()
	{
		for ( auto body : this->bodies )
			if ( body->mass != 0 )
				body->velocity += ( body->force * body->mass + ( this->GRAVITY * body->gravityScale ) ) * this->ups.AsSeconds();
	}

	void SimplePhysicSystem::clearForces()
	{
		for ( auto body : this->bodies )
			body->force = Vec2f::Zero;
	}

	void SimplePhysicSystem::integrateVelocity()
	{
		for ( auto body : this->bodies )
			if ( body->mass != 0 )
				body->position += body->velocity * this->ups.AsSeconds();
	}

	void SimplePhysicSystem::updatePhysic()
	{

		for ( auto& manifold : this->manifolds )
			manifold.Initialize();

		for ( auto& manifold : this->manifolds )
			manifold.CallCallbacks();

		this->clearForces();
	}
}