/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/state/State.hpp>
#include <Core/ecs/Config.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Basic logic operations on Entities and components. You must override systemID_t GetID()
		method.

	===============================================================================
	*/
	class System
	{
	public:
		explicit System( Context cont ) :
			context( std::move( cont ) )
		{}
		virtual ~System() {}

		virtual systemID_t GetID() const = 0;

		virtual void Init() {}
		virtual void Update() {}

	protected:
		Context context;
	};
}