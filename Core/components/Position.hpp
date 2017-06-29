/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Component.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Two floats - x and y.

	===============================================================================
	*/
	struct PositionComponent final : 
		Component
	{
		float x = 0.0f, y = 0.0f;
	};
}