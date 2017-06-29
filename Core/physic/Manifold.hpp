/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/physic/BoundingBox.hpp>

namespace con
{
	// Forward declaration.
	struct SimpleBodyComponent;
	/*
	===============================================================================
	Created by: Condzi
		Class used by PhysicSystem. Contains collision data, collided bodies.

	===============================================================================
	*/
	struct Manifold final
	{
		SimpleBodyComponent* bodyA;
		SimpleBodyComponent* bodyB;
		BoundingBox intersection;
		collisionSide_t collisionSideA = COLLISION_SIDE_NONE;
		collisionSide_t collisionSideB = COLLISION_SIDE_NONE;

		Manifold( SimpleBodyComponent* a, SimpleBodyComponent* b ) :
			bodyA( a ),
			bodyB( b )
		{}
		// Checks if collision occurs.
		bool Check();
		// Initializes Manifold's fields.
		void Initialize();
		void CallCallbacks();

	private:
		void setIntersectison();
		void setCollisionSideA();
	};
}