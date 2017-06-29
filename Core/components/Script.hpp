/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Component.hpp>
#include <Core/Config.hpp>

namespace con
{
	// Forward declarations.
	struct Context;
	struct SimpleBodyComponent;
	enum collisionSide_t : uint8_t;

	/*
	===============================================================================
	Created by: Condzi
		Interface structure for Scripts. Don't forget to call entity.AddScriptComponent!
		It has methods: OnKill(), OnSleep(), OnActive(), FixedUpdate() <called every
		frame>, Update() and OnCollision(first, second, side) <called when collision
		occur>.

	===============================================================================
	*/
	struct ScriptComponent :
		Component
	{
		Context* context = nullptr;

		virtual void OnKill() {}

		virtual void OnSleep() {}
		virtual void OnActive() {}
		// Called every frame even if parent entity is not active.
		virtual void FixedUpdate() {}
		// Called every frame.
		virtual void Update() {}

		virtual void OnCollision( SimpleBodyComponent& first, SimpleBodyComponent& second, collisionSide_t side )
		{
			CON_UNUSED_PARAM( first );
			CON_UNUSED_PARAM( second );
			CON_UNUSED_PARAM( side );
		}
	};
}
