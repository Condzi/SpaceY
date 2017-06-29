#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <Core/state/StateStack.hpp>
#include <Core/Settings.hpp>
#include <Core/resourceManaging/ResourceHolder.hpp>
#include <Core/state/State.hpp>
#include <Core/time/Clock.hpp>
#include <Core/ecs/EntityManager.hpp>
#include <Core/ecs/System.hpp>
#include <Core/ecs/EntityFactory.hpp>
#include <Core/ecs/Messaging.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Game class is a wrapper for State Machine. It does Settings loading and
		creates window.

	===============================================================================
	*/
	class Game final
	{
	public:
		Game( std::string settPath );
		~Game();

		template <typename T, typename... TArgs>
		void AddSystem( TArgs&&... args )
		{
			CON_STATIC_ASSERT( std::is_base_of_v<System, T>, "T must inherit from System" );

			auto sys = std::make_unique<T>( this->context, std::forward<TArgs>( args )... );
			sys->Init();
			this->systems.push_back( std::move( sys ) );
		}

		void RemoveSystem( const systemID_t id )
		{
			this->systems.erase(
				std::remove_if( std::begin( this->systems ), std::end( this->systems ),
					[id]( auto& system )
			{
				return id == system->GetID();
			} ), std::end( this->systems ) );
		}

		template <typename T, typename... TArgs>
		void RegisterState( const stateID_t id, TArgs&&... args )
		{
			this->stateStack.RegisterState<T>( std::move( id ), std::forward<TArgs>( args )... );
		}

		Context GetContext() const
		{
			return this->context;
		}

		void Exit()
		{
			this->exit = true;
		}

		void Run( const stateID_t initState );

	private:
		sf::RenderWindow window;
		EntityManager entityManager;
		ResourceHolder resourceCache;
		Settings settings;
		EntityFactory entityFactory;
		StateStack stateStack;
		Messenger messenger;
		Context context;
		std::vector<std::unique_ptr<System>> systems;
		bool exit;
		std::string settingsPath;

		void assignContextPointers();
		void configureFromSettings();
		void registerDefaultStates();
		void addDefaultSystems();
	};
}
