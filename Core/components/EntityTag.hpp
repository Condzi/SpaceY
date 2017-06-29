/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Component.hpp>

namespace con
{	/*
	===============================================================================
	Created by: Condzi
		Entity Tag component stores uint8_t tag - value that you can assing your entity
		id enum (tag = ENTITY_BALL e.g).

	===============================================================================
	*/
	struct EntityTagComponent final :
		Component
	{
		uint8_t tag = 0;
	};
}