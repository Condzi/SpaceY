/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/components/Drawable.hpp>
#include <Core/components/EntityTag.hpp>
#include <Core/components/Position.hpp>
#include <Core/ecs/EntityFactory.hpp>
#include <Core/Settings.hpp>

#include <Game/Enums.hpp>
#include <Game/scripts/console/ConsoleScript.hpp>
#include <Game/scripts/PlayConsoleStateGameMaster.hpp>

namespace con
{
	struct TextConsoleCreator final :
		EntityCreator
	{
		entityID_t GetID() const override
		{
			return ENTITY_TEXT_CONSOLE;
		}

		void CreateEntity( Entity& entity, Context& context ) override
		{
			entity.AddComponent<PositionComponent>();
			entity.AddComponent<DrawableComponent>().drawLayer = LAYER_TEXT;
			entity.AddComponent<EntityTagComponent>().tag = ENTITY_TEXT_CONSOLE;
			entity.AddGroup( GROUP_PLAY_STATE_CONSOLE );
		}
	};

	struct DrawableEntityCreator final :
		EntityCreator
	{
		entityID_t GetID() const override
		{
			return ENTITY_SPRITE;
		}

		void CreateEntity( Entity& entity, Context& context ) override
		{
		//	entity.AddComponent<PositionComponent>();
			entity.AddComponent<DrawableComponent>();
			entity.AddComponent<EntityTagComponent>().tag = ENTITY_SPRITE;
		}
	};

	struct ConsoleCreator final :
		EntityCreator
	{
		entityID_t GetID() const override
		{
			return ENTITY_CONSOLE;
		}

		void CreateEntity( Entity& entity, Context& context ) override
		{
			entity.AddComponent<EntityTagComponent>().tag = ENTITY_CONSOLE;
			entity.AddScriptComponent<ConsoleScript>( context );
			entity.AddGroup( GROUP_PLAY_STATE_CONSOLE );
		}
	};

	struct PlayConsoleStateGameMasterCreator final :
		EntityCreator
	{
		entityID_t GetID() const override
		{
			return ENTITY_PLAY_CONSOLE_STATE_GAME_MASTER;
		}

		void CreateEntity( Entity& entity, Context& context ) override
		{
			entity.AddComponent<EntityTagComponent>().tag = ENTITY_PLAY_CONSOLE_STATE_GAME_MASTER;
			entity.AddScriptComponent<PlayConsoleStateGameMaster>( context );
			entity.AddGroup( GROUP_PLAY_STATE_CONSOLE );
		}
	};
}