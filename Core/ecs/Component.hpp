/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Config.hpp>

namespace con
{
	// Forward declaration.
	class Entity;

	/*
	===============================================================================
	Created by: Condzi
		Provides basic interface for components. Be careful with dependencies (X component
		needs Y component to work), make sure that you are adding X component after Y - 
		if you try to add it before Y you'll get a invalid pointer (but before that ASSERT 
		should come in).

	===============================================================================
	*/
	struct Component
	{
		Entity* entity;

		virtual ~Component() {}

		virtual void Init() {}
	};
}