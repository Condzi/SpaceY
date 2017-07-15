#include <Core/state/Game.hpp>
#include <Core/systems/PositionUpdate.hpp>
#include <Core/systems/SimplePhysic.hpp>
#include <Core/systems/ScriptUpdate.hpp>
#include <Core/systems/Renderer.hpp>
#include <Core/state/DebugData.hpp>
#include <Core/Config.hpp>

namespace con {
Game::Game()
{
	LOG( "Game ctor; application start", INFO, BOTH );

	this->assignContextPointers();

	this->loadSettings();
	this->configureFromSettings();

	this->addDefaultSystems();
	this->registerDefaultStates();
}

Game::~Game()
{
	LOG( "Saving settings...", INFO, BOTH );
	this->settingsEngine.Save();
	this->settingsGame.Save();
	LOG( "Cleaning up...", INFO, BOTH );
	this->resourceCache.DeleteAllResources();
}

void Game::Run( const stateID_t initState )
{
	this->stateStack.Push( std::move( initState ) );
	this->stateStack.ApplyPendingActions();

	Clock clock;

	while ( !this->exit && this->stateStack.GetStateOnTop() != (stateID_t)coreStates_t::EXIT ) {
		this->pollEvents();
		this->update();

		Time::FRAME_TIME = clock.Restart();
	}
}

void Game::pollEvents()
{
	sf::Event event;
	while ( this->window.pollEvent( event ) ) {
		if ( event.type == sf::Event::Closed ) {
			this->Exit();
			break;
		}

		// IDEA: Add same thing to update() and maybe setting / constexpr 'LOCK_UPDATE(or event)_WHEN_NO_FOCUS'
		// Don't update input if window doesn't have focus.
		if ( !this->window.hasFocus() )
			continue;
		// Copies temporary sf::Event state and mark it to delete at end of the loop.
		this->messenger.AddMessage( (messageID_t)coreMessages_t::INPUT_EVENT, sf::Event( event ) )->safeDelete = true;
	}
}

void Game::update()
{
	for ( auto& system : this->systems )
		system->Update();
	this->stateStack.Update();
	this->messenger.ClearMessages();

	this->entityManager.Refresh();
	this->stateStack.ApplyPendingActions();
}

void Game::assignContextPointers()
{
	this->context.window = &this->window;
	this->context.entityManager = &this->entityManager;
	this->context.resourceCache = &this->resourceCache;
	this->context.settingsEngine = &this->settingsEngine;
	this->context.settingsGame = &this->settingsGame;
	this->context.entityFactory = &this->entityFactory;
	this->context.stateStack = &this->stateStack;
	this->context.messenger = &this->messenger;

	this->stateStack.SetContext( this->context );
}

void Game::loadSettings()
{
	this->settingsEngine.Load( PATH_ENGINE_SETTINGS );
	if ( !this->settingsEngine.DoesMatchWithDefault() ) {
		LOG( "Generating default engine settings", INFO, CONSOLE );
		this->settingsEngine.CreateDefault();
	}

	this->settingsGame.Load( PATH_GAME_SETTINGS );
	if ( !this->settingsGame.DoesMatchWithDefault() ) {
		LOG( "Generating default game settings", INFO, CONSOLE );
		this->settingsGame.CreateDefault();
	}
}

void Game::configureFromSettings()
{
	auto winX = To<uint32_t>( *this->settingsEngine.Get( "WINDOW", "SIZE_X" ) );
	auto winY = To<uint32_t>( *this->settingsEngine.Get( "WINDOW", "SIZE_Y" ) );
	auto winTitlePtr = this->settingsGame.Get( "DEFAULT", "NAME" );
	auto winTitle = winTitlePtr ? *winTitlePtr : "ConEngine";
	auto fps = To<uint32_t>( *this->settingsEngine.Get( "WINDOW", "FPS" ) );

	this->window.create( { winX, winY }, winTitle, sf::Style::Close | sf::Style::Resize );
	this->window.setFramerateLimit( fps );

}

void Game::registerDefaultStates()
{
	auto debugStrVal = this->settingsEngine.Get( "DEBUG", "DEBUG_DATA" );
	bool addDebugDataState = debugStrVal != nullptr ? To<bool>( *debugStrVal ) : false;

	this->RegisterState<ExitState>( To<stateID_t>( coreStates_t::EXIT ) );
	if ( addDebugDataState ) {
		this->RegisterState<DebugDataState>( To<stateID_t>( coreStates_t::DEBUG_DATA ) );
		this->stateStack.Push( To<stateID_t>( coreStates_t::DEBUG_DATA ) );
	}
}

void Game::addDefaultSystems()
{
	this->AddSystem<PositionUpdateSystem>();
	this->AddSystem<SimplePhysicSystem>();
	this->AddSystem<ScriptUpdateSystem>();
	this->AddSystem<Renderer>();
}
}