/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/resourceManaging/ResourceHolder.hpp>
#include <Core/state/State.hpp>
#include <Core/ecs/Entity.hpp>
#include <Core/ecs/EntityFactory.hpp>
#include <Core/components/Drawable.hpp>
#include <Core/components/Position.hpp>

#include <Game/Enums.hpp>
#include <Game/EntityCreators.hpp>

namespace con
{
	class LoadingScreenState final :
		public State
	{
	public:
		LoadingScreenState( StateStack& stack, Context cont ) :
			State( stack, cont )
		{}

		stateID_t GetID() const override { return STATE_LOADING_SCREEN; }

		void OnPush() override
		{
			this->StartThread();
		}
		void OnPop() override
		{
			this->StopThread();
		}

		// Loads and configures everything.
		void UpdateThread() override
		{
			// Thread tries to call UpdateThread multiple times; until StateStack call OnPop and stop this madness.
			if ( this->resourcesLoaded )
				return;
			this->resourcesLoaded = true;
			this->loadTextures();
			this->loadFonts();
			this->registerEntityCreators();

			this->requestStackPop();
			// IMPORTANT: Temporary.
			this->requestStackPush( STATE_PLAY_CONSOLE );
		}

	private:
		bool resourcesLoaded = false;
		void loadTextures()
		{
			auto& cache = this->context.resourceCache->textures;

			cache.emplace_back( std::make_unique<textureResource_t>( RESOURCE_MULTISTATE, TEXTURE_ATLAS ) );
			auto& sheet = cache.back();
			if ( !sheet->loadFromFile( "data/texture_atlas.png" ) )
			{
				cache.pop_back();
				LOG( "Cannot load data/texture_atlas.png", ERROR, BOTH );
			}
		}

		void loadFonts()
		{
			auto& cache = this->context.resourceCache;

			cache->fonts.emplace_back( std::make_unique<fontResource_t>( RESOURCE_MULTISTATE, FONT_CONSOLAS ) );
			auto& font = cache->fonts.back();
			if ( !font->loadFromFile( "data/consolas.ttf" ) )
			{
				cache->fonts.pop_back();
				LOG( "Cannot load data/consolas.ttf", ERROR, BOTH );
			}
		}

		void registerEntityCreators()
		{
			auto& entityFactory = *this->context.entityFactory;

			entityFactory.AddCreator<TextConsoleCreator>();
			entityFactory.AddCreator<ConsoleCreator>();
			entityFactory.AddCreator<PlayConsoleStateGameMasterCreator>();
			entityFactory.AddCreator<DrawableEntityCreator>();
		}
	};
}