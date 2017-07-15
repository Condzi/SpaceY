/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Settings.hpp>

namespace sf {
class RenderWindow;
}

namespace con {
// Forward declaration.
class EntityManager;
struct ResourceHolder;
class Game;
class EntityFactory;
class StateStack;
class Messenger;

/*
===============================================================================
Created by: Condzi
	Special structure that gives you access to core objects: window, entityManager,
	resourceCache, settings, entityFactory, stateStack and game. Most
	of them requires to include it's file (e.g resourceCache requires to use
	include <Core/resourceManaging/ResourceHolder.hpp>).

===============================================================================
*/
struct Context final
{
	sf::RenderWindow* window = nullptr;
	EntityManager* entityManager = nullptr;
	ResourceHolder* resourceCache = nullptr;
	Settings<SETTINGS_ENGINE>* settingsEngine = nullptr;
	Settings<SETTINGS_GAME>* settingsGame = nullptr;
	EntityFactory* entityFactory = nullptr;
	StateStack* stateStack = nullptr;
	Messenger* messenger = nullptr;
	Game* game = nullptr;
};
}