#pragma once

#include <atomic>
#include <thread>
#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>

#include <Core/Assert.hpp>
#include <Core/logger/Logger.hpp>
#include <Core/Config.hpp>

namespace con
{
	// Forward declaration.
	class EntityManager;
	struct ResourceHolder;
	class Settings;
	class Game;
	class EntityFactory;
	class StateStack;
	class Messenger;

	/*
	===============================================================================
	Created by: Condzi
		Special structure that gives you acces to core objects: window, entityManager,
		resourceCache, settings, entityFactory, stateStack and game. Most
		of them requiers to include it's file (e.g resourceCache requiers to use
		include <Core/resourceManaging/ResourceHolder.hpp>).

	===============================================================================
	*/
	struct Context final
	{
		explicit Context( Game* g = nullptr );
		sf::RenderWindow* window = nullptr;
		EntityManager* entityManager = nullptr;
		ResourceHolder* resourceCache = nullptr;
		Settings* settings = nullptr;
		EntityFactory* entityFactory = nullptr;
		StateStack* stateStack = nullptr;
		Messenger* messenger = nullptr;
		Game* game;
	};

	/*
	===============================================================================
	Created by: Condzi
		Virtual State class. You can make loading screen with it. You must overwrite
		stateID_t GetID. You may also override OnPush, OnPop and Update().

	===============================================================================
	*/
	class State
	{
	public:
		State( StateStack& stack, Context cont ) :
			stateStack( stack ),
			context( std::move( cont ) ),
			threadRunning( false )
		{}
		virtual ~State()
		{
			if ( this->threadRunning )
				this->StopThread();
		}

		State( const State& ) = delete;
		const State& operator= ( const State& ) = delete;

		virtual stateID_t GetID() const = 0;
		virtual void OnPush() {};
		virtual void OnPop() {};
		virtual void Update() {}

		// Call it when you need to load resources and you don't want to freeze window
		// Don't forget to call EndThread() 
		void StartThread();
		void StopThread();
		virtual void UpdateThread() {};

	protected:
		Context context;

		void requestStackPush( const stateID_t id );
		void requestStackPop();
		// You may want to use it to update only when this state is currently active. 
		// For example: you probably don't want to update game AI, mobs etc. when Pause state is on top.
		bool imStateOnTopOfTheStack();
		stateID_t getStateOnTopOfTheStack();

	private:
		std::thread thread;
		std::atomic_bool threadRunning;
		StateStack& stateStack;

		void threadloop();
	};

	/*
	===============================================================================
	Created by: Condzi
		If you push this state to StateStack it'll be equal to 'context.game->Exit().

	===============================================================================
	*/
	class ExitState final :
		public State
	{
	public:
		ExitState( StateStack& stack, Context cont ) :
			State( stack, std::move( cont ) )
		{}

		stateID_t GetID() const override
		{
			return EXIT_STATE;
		}
	};
}