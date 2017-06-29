/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/logger/Logger.hpp>
#include <Core/physic/CollisionReaction.hpp>

namespace con
{
	namespace CollisionReaction
	{
		void CorrectPositionAfterCollision( SimpleBodyComponent& first, const SimpleBodyComponent& second, collisionSide_t side )
		{
			if ( (first.lockXaxis && first.lockYaxis) || first.mass == 0)
				return;

			if ( !first.lockXaxis )
			{
				if ( side == COLLISION_SIDE_LEFT )
					first.position.x = second.position.x - first.bb.size.x;
				else if ( side == COLLISION_SIDE_RIGHT )
					first.position.x = second.position.x + second.bb.size.x;
			}
			if ( !first.lockYaxis )
			{
				if ( side == COLLISION_SIDE_TOP )
					first.position.y = second.position.y + second.bb.size.y;
				else if ( side == COLLISION_SIDE_BOTTOM )
					first.position.y = second.position.y - first.bb.size.y;
			}
		}

		void StopInCollisionAxis( SimpleBodyComponent& body, collisionSide_t side )
		{
			if ( side == COLLISION_SIDE_NONE )
			{
				DEBUG_LOG( "StopInCollisionAxis call with side == COLLISION_SIDE_NONE", WARNING, CONSOLE );
				return;
			}

			if ( side == COLLISION_SIDE_LEFT || side == COLLISION_SIDE_RIGHT )
				body.velocity.x = 0.0f;
			else
				body.velocity.y = 0.0f;
		}
	}
}