/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Vec2.hpp>

namespace con
{
	enum collisionSide_t : uint8_t
	{
		COLLISION_SIDE_NONE = 0,

		COLLISION_SIDE_LEFT,
		COLLISION_SIDE_RIGHT,
		COLLISION_SIDE_TOP,
		COLLISION_SIDE_BOTTOM,
	};

	inline collisionSide_t invertCollisionSide( const collisionSide_t src )
	{
		switch ( src )
		{
		case COLLISION_SIDE_LEFT: return COLLISION_SIDE_RIGHT;
		case COLLISION_SIDE_RIGHT: return COLLISION_SIDE_LEFT;
		case COLLISION_SIDE_TOP: return COLLISION_SIDE_BOTTOM;
		case COLLISION_SIDE_BOTTOM: return COLLISION_SIDE_TOP;
		case COLLISION_SIDE_NONE: return COLLISION_SIDE_NONE;
		}
		return COLLISION_SIDE_NONE;
	}

	/*
	===============================================================================
	Created by: Condzi
		2D rectangle, Axis Aligned Bounding Box, used for collision detection>.

	===============================================================================
	*/
	struct BoundingBox final
	{
		Vec2f position;
		Vec2f size;

		BoundingBox( Vec2f pos = Vec2f::Zero, Vec2f sz = Vec2f::Zero ) :
			position( std::move( pos ) ), size( std::move( sz ) )
		{}
		BoundingBox( float x, float y, float width, float height ) :
			position( std::move( x ), std::move( y ) ), size( std::move( width ), std::move( height ) )
		{}
	};
}