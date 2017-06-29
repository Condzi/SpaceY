/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/System/Err.hpp>

#include <Core/state/Game.hpp>

#include <Game/states/LoadingScreen.hpp>

using namespace con;

int main()
{
	// Redirect SFML error stream to text file.
	std::ofstream sfmlOutput( "sfml_output.txt" );
	sf::err().rdbuf( sfmlOutput.rdbuf() );

#if !defined DEBUG
	bool exitProperly = true;
	{
		try
		#endif // DEBUG
		{
			Game game( "settings.ini" );
			game.RegisterState<LoadingScreenState>( STATE_LOADING_SCREEN );

			game.Run( STATE_LOADING_SCREEN );
		}
	#if !defined DEBUG
		catch ( BaseException& baseException )
		{
			LOG( "Base Exception (assert) thrown.", ERROR, BOTH );
			showBasicExceptionData( baseException );
			exitProperly = false;
		}
		catch ( std::runtime_error& runtime )
		{
			LOG( "Runtime Exception thrown.", ERROR, BOTH );
			LOG( "Exception data: \"" << runtime.what() << "\"", ERROR, BOTH );
			exitProperly = false;
		}
		catch ( std::exception& ex )
		{
			LOG( "Exception thrown.", ERROR, BOTH );
			LOG( "Exception data: \"" << ex.what() << "\"", ERROR, BOTH );
			exitProperly = false;
		}

		if ( !exitProperly )
		{
			LOG( "Press enter to exit.", INFO, CONSOLE );
			std::cin.get();
		} else
		{
			LOG( "Game exited properly.", INFO, BOTH );
		}
	}

	return exitProperly ? 0 : 1;
#else
		return 0;
	#endif
}