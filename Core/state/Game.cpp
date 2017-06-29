#include <Core/state/Game.hpp>
#include <Core/systems/PositionUpdate.hpp>
#include <Core/systems/SimplePhysic.hpp>
#include <Core/systems/ScriptUpdate.hpp>
#include <Core/systems/Renderer.hpp>
#include <Core/state/DebugData.hpp>

namespace con
{
	Game::Game( std::string settPath ) :
		settingsPath( std::move( settPath ) ),
		context( this )
	{
		LOG( "Game ctor; application start", INFO, BOTH );
		this->assignContextPointers();

		if ( !this->settings.LoadFromFile( this->settingsPath ) )
			this->settings.GenerateDefault( this->settingsPath );
		else
			this->settings.Parse();

		this->configureFromSettings();

		this->addDefaultSystems();
		this->registerDefaultStates();
	}

	Game::~Game()
	{
		LOG( "Saving settings...", INFO, BOTH );
		this->settings.SaveToFile( this->settingsPath, "; Default config. Don't change if you don't know what are you doing!" );
		LOG( "Cleaning up...", INFO, BOTH );
		this->resourceCache.DeleteAllResources();
	}

	void Game::Run( const stateID_t initState )
	{
		this->stateStack.Push( std::move( initState ) );
		this->stateStack.ApplyPendingActions();

		Clock clock;
		sf::Event event;

		while ( !exit && this->stateStack.GetStateOnTop() != EXIT_STATE )
		{
			while ( this->window.pollEvent( event ) )
			{
				if ( event.type == sf::Event::Closed )
					this->Exit();
			}
			for ( auto& system : this->systems )
				system->Update();
			this->stateStack.Update();
			this->messenger.ClearMessages();

			this->entityManager.Refresh();
			this->stateStack.ApplyPendingActions();
			Time::FRAME_TIME = clock.Restart();
		}
	}

	void Game::assignContextPointers()
	{
		this->context.window = &this->window;
		this->context.entityManager = &this->entityManager;
		this->context.resourceCache = &this->resourceCache;
		this->context.settings = &this->settings;
		this->context.entityFactory = &this->entityFactory;
		this->context.stateStack = &this->stateStack;
		this->context.messenger = &this->messenger;
		this->stateStack.SetContext( this->context );
	}

	void Game::configureFromSettings()
	{
		INIError_t error;

		this->window.create(
		{ static_cast<uint32_t>( this->settings.GetInt( "WINDOW", "X", &error ) ),
			static_cast<uint32_t>( this->settings.GetInt( "WINDOW", "Y", &error ) ) },
			this->settings.GetString( "WINDOW", "TITLE", &error ),
			sf::Style::Close | sf::Style::Resize );
		this->window.setFramerateLimit( this->settings.GetInt( "WINDOW", "FPS", &error ) );

		// IDEA: Move later to Settings::CheckAreDefaultInitialized or something.
		this->settings.GetInt( "PHYSIC", "UPS", &error );
		this->settings.GetString( "WINDOW", "TITLE", &error );
		this->settings.GetInt( "WINDOW", "FPS", &error );
		this->settings.GetInt( "WINDOW", "X", &error );
		this->settings.GetInt( "WINDOW", "Y", &error );
		this->settings.GetInt( "WINDOW", "DESIGNED_X", &error );
		this->settings.GetInt( "WINDOW", "DESIGNED_Y", &error );
		this->settings.GetInt( "SOUND", "VOLUME", &error );

		if ( !error.what.empty() )
		{
			LOG( "One or more errors occured loading basic engine settings, generating default.", WARNING, BOTH );
			this->settings.GenerateDefault( this->settingsPath );
			this->configureFromSettings();
		}
	}

	void Game::registerDefaultStates()
	{
		this->RegisterState<ExitState>( EXIT_STATE );
		if ( this->GetContext().settings->GetBool( "DEBUG", "DEBUG_DATA" ) )
		{
			this->RegisterState<DebugDataState>( DEBUG_DATA_STATE );
			this->stateStack.Push( DEBUG_DATA_STATE );
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