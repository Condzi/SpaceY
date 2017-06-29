#pragma once

#include <Core/Config.hpp>
#include <Core/fileManaging/INIparser.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Simple extension for INIFile class. To get settings simple use Get methods from
		INIFile.

	===============================================================================
	*/
	class Settings final :
		public INIFile
	{
	public:
		void GenerateDefault( const std::string& path )
		{
			// IDEA: constexpr 3D demensional table with this values?
			this->AddString( "WINDOW", "TITLE", GAME_NAME );
			this->AddInt( "WINDOW", "FPS", 60 );
			this->AddInt( "WINDOW", "X", 1280 );
			this->AddInt( "WINDOW", "Y", 720 );
			this->AddInt( "WINDOW", "DESIGNED_X", 1920 );
			this->AddInt( "WINDOW", "DESIGNED_Y", 1080 );
			this->AddInt( "PHYSIC", "UPS", 60 );
			this->AddInt( "SOUND", "VOLUME", 100 );

			this->SaveToFile( path, "; Default config. Don't change if you don't know what are you doing!" );
		}
	};
}