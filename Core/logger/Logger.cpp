/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#if defined _WIN32
#define NOMINMAX
#include <Windows.h>
#undef ERROR
#endif // _WIN32
#include <Core/logger/Logger.hpp>

namespace con
{
	namespace internal
	{
		void setConsoleTextColor( const uint8_t col )
		{
		#if defined _WIN32
			HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if ( GetConsoleScreenBufferInfo( hStdOut, &csbi ) )
			{
				WORD wColor = ( csbi.wAttributes & 0xF0 ) + ( col & 0x0F );
				SetConsoleTextAttribute( hStdOut, wColor );
			}
		#endif // _WIN32
		}
	}

	void Logger::Log( std::ostream& message, const prefix_t prefix, const output_t output )
	{
		static Logger instance;
		std::stringstream finalMessage;

		switch ( prefix )
		{
		case INFO: finalMessage << "[  INFO   I"; break;
		case WARNING: finalMessage << "[ WARNING I"; break;
		case ERROR: finalMessage << "[  ERROR  I"; break;
		}

		auto now = std::chrono::system_clock::now();
		auto timer = std::chrono::system_clock::to_time_t( now );
		std::tm bt;
	#if defined _MSC_VER
		localtime_s( &bt, &timer );
	#else
		bt = *std::localtime( &timer );
	#endif

		finalMessage << std::put_time( &bt, " %T ] " );
		finalMessage << dynamic_cast<std::ostringstream&>( message ).str() << "\n";

		if ( output == CONSOLE || output == BOTH )
		{
			internal::setConsoleTextColor( prefix );
			instance.logToConsole( finalMessage.str() );
		}
		if ( output == FILE || output == BOTH )
			instance.logToFile( finalMessage.str() );
	}

	Logger::Logger()
	{
	#if defined _WIN32
		SetConsoleTitle( "Game Log" );
	#endif // _WIN32

		this->outputFile.open( "output.txt" );
		if ( !this->outputFile.is_open() )
			LOG( "Cannot open log file", ERROR, CONSOLE );
	}

	void Logger::logToConsole( std::string message )
	{
		std::cerr << message;
	}

	void Logger::logToFile( std::string message )
	{
		this->outputFile << message;
		this->outputFile.flush();
	}
}