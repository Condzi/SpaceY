/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <array>

#include <Core/Config.hpp>
#include <Core/Exception.hpp>
#include "INIFile.hpp"
#include "ConstexprStructures.hpp"

namespace con {
namespace experimental {

enum settings_t : uint8_t
{
	SETTINGS_DEFAULT_ENGINE,
	SETTINGS_DEFAULT_GAME,

	SETTINGS_ENGINE,
	SETTINGS_GAME
};
// TODO: Move to Config.hpp
constexpr uint8_t MAX_SETTINGS_RECORDS = 255;

// TODO: Improve this macros so they may auto format better.
#define BEGIN_SETTINGS_DEF \
	static constexpr std::array<constexprRecord_t, MAX_SETTINGS_RECORDS> records = {

#define DEFINE_SETTING( SECTION, NAME, VALUE ) constexprRecord_t( SECTION, NAME, VALUE )

#define END_SETTINGS_DEF }; \
static constexpr constexprString_t Get( const constexprString_t& section, const constexprString_t& name ) \
{ \
	auto result = constexprFindIf( \
		Settings<SETTINGS_DEFAULT_ENGINE>::records.begin(), \
		Settings<SETTINGS_DEFAULT_ENGINE>::records.end(), \
		[section, name]( const constexprRecord_t& record ) \
	{ \
		return ( section == record.section ) && ( name == record.name ); \
	} ); \
	if ( result == Settings<SETTINGS_DEFAULT_ENGINE>::records.end() ) \
		return constexprString_t( "" ); \
	return result->value; \
}

namespace internal
{
	// TODO: Move to Exception.hpp
	class NotImplemented :
		public BasicException
	{
	public:
		NotImplemented( std::string wFile, std::string wFunction, uint32_t wLine, std::string wMessage ) :
			BasicException( wFile, wFunction, wLine, "no condition", wMessage )
		{}
	};
	// TODO: Move to Assert.hpp ?
#define CON_THROW( message, exceptionClass ) \
	throw exceptionClass(__FILE__, __func__, __LINE__, message )

	struct SettingsInterface
	{
		virtual bool Load( const std::string path )
		{
			CON_UNUSED_PARAM( path );
			CON_THROW( "method specially not implemented, don't use it", NotImplemented );
		}
		virtual bool DoesMatchWithDefault()
		{
			CON_THROW( "method specially not implemented, don't use it", NotImplemented );
		}
		virtual bool CreateDefault()
		{
			CON_THROW( "method specially not implemented, don't use it", NotImplemented );
		}
		virtual bool SaveCurrent()
		{
			CON_THROW( "method specially not implemented, don't use it", NotImplemented );
		}
		virtual std::string* Get( const std::string& section, const std::string& name )
		{
			CON_UNUSED_PARAM( section );
			CON_UNUSED_PARAM( name );
			CON_THROW( "method specially not implemented, don't use it", NotImplemented );
		}
	};
}
// Dummy
template <settings_t T>
struct Settings final :
	internal::SettingsInterface
{};

template <>
struct Settings<SETTINGS_DEFAULT_ENGINE> final
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

template<>
struct Settings<SETTINGS_ENGINE> final :
	internal::SettingsInterface
{
	bool Load( const std::string path ) override
	{
		if ( !this->file.Open( path ) )
			return false;
		this->file.Parse();
		return true;
	}

	bool DoesMatchWithDefault() override
	{
		for ( auto& record : Settings<SETTINGS_DEFAULT_ENGINE>::records )
			if ( !this->file.GetValuePtr( record.section.data, record.name.data ) )
				return false;

		return true;
	}

	bool CreateDefault() override
	{
		this->file.Clear();

		for ( auto& record : Settings<SETTINGS_DEFAULT_ENGINE>::records )
			if ( !record.SkipWhenSaving() )
				this->file.AddValue( record.section.data, record.name.data, record.value.data );

		return this->file.Save();
	}

	bool SaveCurrent() override
	{
		return this->file.Save();
	}

	std::string* Get( const std::string& section, const std::string& name ) override
	{
		return file.GetValuePtr( section, name );
	}

private:
	INIFile file;
};



}
}