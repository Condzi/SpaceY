/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <array>

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
		constexpr uint8_t MAX_SETTINGS_RECORDS = 255;

		// TODO: Improve this macros so they may auto format better.
	#define BEGIN_SETTINGS_DEF													\
		static constexpr std::array<record_t, MAX_SETTINGS_RECORDS> records =   \
		{

	#define DEFINE_SETTING( SECTION, NAME, VALUE )					\
		record_t( SECTION, NAME, VALUE )

	#define END_SETTINGS_DEF										\
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


			static constexpr constexprString_t Get( const constexprString_t& section, const constexprString_t& name )
			{
				auto result = constexprFindIf( 
					DefaultSettings<SETTINGS_DEFAULT_ENGINE>::records.begin(), 
					DefaultSettings<SETTINGS_DEFAULT_ENGINE>::records.end(),
					[section, name]( const record_t& record )
				{
					return ( section == record.section ) && ( name == record.name );
				} );
				if ( result == DefaultSettings<SETTINGS_DEFAULT_ENGINE>::records.end() )
					return constexprString_t( "" );

				return result->value;
			}

		};

		struct Settings
		{

		};
	}
}