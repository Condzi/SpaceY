/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/physic/Manifold.hpp>
#include <Core/components/SimpleBody.hpp>
#include <Core/components/Script.hpp>
#include <Core/ecs/Entity.hpp>
#include <Core/Assert.hpp>

namespace con
{
	bool Manifold::Check()
	{
		this->setIntersectison();
		if ( !( this->intersection.position.x < this->intersection.position.x + this->intersection.size.x &&
			this->intersection.position.y < this->intersection.position.y + this->intersection.size.y ) )
		{
			this->collisionSideA = this->collisionSideB = COLLISION_SIDE_NONE;
			return false;
		}

		return true;
	}

	void Manifold::Initialize()
	{
		this->setCollisionSideA();
		this->collisionSideB = invertCollisionSide( this->collisionSideA );
	}

	void Manifold::CallCallbacks()
	{
		if ( this->bodyA->entity->HasComponent<ScriptComponent>() )
			this->bodyA->entity->GetComponent<ScriptComponent>().OnCollision( *this->bodyA, *this->bodyB, this->collisionSideA );
	//	if ( this->bodyB->entity->HasComponent<ScriptComponent>() )
	//		this->bodyB->entity->GetComponent<ScriptComponent>().OnCollision( *this->bodyB, *this->bodyA, this->collisionSideB );
	}

	void Manifold::setIntersectison()
	{
		BoundingBox first = this->bodyA->bb;
		first.position += this->bodyA->position;
		BoundingBox second = this->bodyB->bb;
		second.position += this->bodyB->position;

		// Rectangles with negative dimensions are allowed, so we must handle them correctly
		// Compute the min and max of the first rectangle on both axes
		auto r1MinX = std::min( first.position.x, ( first.position.x + first.size.x ) );
		auto r1MaxX = std::max( first.position.x, ( first.position.x + first.size.x ) );
		auto r1MinY = std::min( first.position.y, ( first.position.y + first.size.y ) );
		auto r1MaxY = std::max( first.position.y, ( first.position.y + first.size.y ) );
		// Compute the min and max of the second rectangle on both axes
		auto r2MinX = std::min( second.position.x, ( second.position.x + second.size.x ) );
		auto r2MaxX = std::max( second.position.x, ( second.position.x + second.size.x ) );
		auto r2MinY = std::min( second.position.y, ( second.position.y + second.size.y ) );
		auto r2MaxY = std::max( second.position.y, ( second.position.y + second.size.y ) );
		// Compute the intersection boundaries
		auto interLeft = std::max( r1MinX, r2MinX );
		auto interTop = std::max( r1MinY, r2MinY );
		auto interRight = std::min( r1MaxX, r2MaxX );
		auto interBottom = std::min( r1MaxY, r2MaxY );

		this->intersection = BoundingBox( interLeft, interTop, interRight - interLeft, interBottom - interTop );
	}

	void Manifold::setCollisionSideA()
	{
		const Vec2f& firstPosition = this->bodyA->position;
		const Vec2f& secondPosition = this->bodyB->position;

		if ( this->intersection.size.x > this->intersection.size.y )
		{
			if ( firstPosition.y > secondPosition.y )
				this->collisionSideA = COLLISION_SIDE_TOP;
			else
				this->collisionSideA = COLLISION_SIDE_BOTTOM;
		} else
		{
			if ( firstPosition.x < secondPosition.x )
				this->collisionSideA = COLLISION_SIDE_LEFT;
			else
				this->collisionSideA = COLLISION_SIDE_RIGHT;
		}

		CON_ASSERT( this->collisionSideA != COLLISION_SIDE_NONE, "collision detected but cannot find its side" );
	}
}