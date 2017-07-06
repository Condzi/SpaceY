/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/components/EntityTag.hpp>
#include <Core/ecs/EntityFactory.hpp>
#include <Core/Settings.hpp>

#include <Game/Enums.hpp>
#include <Game/scripts/console/ConsoleScript.hpp>

namespace con
{
	struct TextConsoleCreator final :
		EntityCreator
	{
		entityID_t GetID() const override
		{
			return ENTITY_TEXT_CONSOLE;
		}

		void CreateEntity( Entity& entity, Context& context )
		{
			entity.AddComponent<PositionComponent>();
			entity.AddComponent<DrawableComponent>().drawLayer = LAYER_TEXT;
			entity.AddComponent<EntityTagComponent>().tag = ENTITY_TEXT_CONSOLE;
			entity.AddGroup( GROUP_PLAY_STATE_CONSOLE );
		}
	};

	struct ConsoleCreator final :
		EntityCreator
	{
		entityID_t GetID() const override
		{
			return ENTITY_CONSOLE;
		}

		void CreateEntity( Entity& entity, Context& context )
		{
			entity.AddComponent<EntityTagComponent>().tag = ENTITY_CONSOLE;
			entity.AddScriptComponent<ConsoleScript>( context );
			entity.AddGroup( GROUP_PLAY_STATE_CONSOLE );
		}
	};
}