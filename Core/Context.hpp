/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

namespace sf
{
	class RenderWindow;
}

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
		sf::RenderWindow* window = nullptr;
		EntityManager* entityManager = nullptr;
		ResourceHolder* resourceCache = nullptr;
		Settings* settings = nullptr;
		EntityFactory* entityFactory = nullptr;
		StateStack* stateStack = nullptr;
		Messenger* messenger = nullptr;
		Game* game = nullptr;
	};
}