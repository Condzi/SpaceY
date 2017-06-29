/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/System.hpp>
#include <Core/ecs/Functions.hpp>
#include <Core/components/Script.hpp>
// For Context structure.
#include <Core/state/State.hpp>
#include <Core/ecs/EntityManager.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Calls FixedUpdate and Update on every entity with ScriptComponent.

	===============================================================================
	*/
	class ScriptUpdateSystem final :
		public System
	{
	public:
		ScriptUpdateSystem( Context cont ) :
			System( std::move( cont ) )
		{}

		systemID_t GetID() const override
		{
			return 2;
		}

		void Init() override
		{
			this->signature = createComponentSignature( getComponentTypeID<ScriptComponent>() );
		}

		void Update() override
		{
			auto vec = this->context.entityManager->GetEntitiesWithSignature( this->signature );

			for ( auto entity : vec )
			{
				auto& scriptComponent = entity->GetComponent<ScriptComponent>();

				scriptComponent.FixedUpdate();
				if ( entity->IsAlive() && entity->IsActive() )
					scriptComponent.Update();
			}
		}

	private:
		componentBitset_t signature;
	};
}