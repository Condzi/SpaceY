/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Config.hpp>
#include "INIFile.hpp"
#include "ConstexprStructures.hpp"

namespace con
{
	namespace experimental
	{
		enum defaultSettings_t
		{
			SETTINGS_DEFAULT_ENGINE,
			SETTINGS_DEFAULT_GAME
		};

	// TODO: Improve this macros so they may auto format better.
	#define BEGIN_SETTINGS_DEF										\
		static constexpr record_t records[] =						\
		{

	#define DEFINE_SETTING( SECTION, NAME, VALUE )					\
		record_t( SECTION, NAME, VALUE )

	#define END_SETTINGS_DEF										\
		};

		struct record_t final // compile time version of INIFile::record_t
		{
			constexprString_t section, name, value;
			constexpr record_t( constexprString_t _section, constexprString_t _name, constexprString_t _value ) :
				section( std::move( _section ) ),
				name( std::move( _name ) ),
				value( std::move( _value ) )
			{}
		};

		// Dummy
		template <defaultSettings_t T>
		struct DefaultSettings final
		{};

		template <>
		struct DefaultSettings<SETTINGS_DEFAULT_ENGINE> final
		{
			BEGIN_SETTINGS_DEF

				DEFINE_SETTING( "WINDOW", "TITLE", "ConEngine" ),
				DEFINE_SETTING( "WINDOW", "FPS", "60" ),
				DEFINE_SETTING( "WINDOW", "SIZE_X", "1280" ),
				DEFINE_SETTING( "WINDOW", "SIZE_Y", "720" ),

				DEFINE_SETTING( "AUDIO", "MASTER_VOLUME", "100" ),
				DEFINE_SETTING( "AUDIO", "MUSIC_VOLUME", "100" ),
				DEFINE_SETTING( "AUDIO", "SOUND_VOLUME", "100" ),

				DEFINE_SETTING( "PHYSIC", "UPS", "60" )

				END_SETTINGS_DEF
		};

		struct Settings
		{

		};
	}
}