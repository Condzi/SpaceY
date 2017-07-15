/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

// for exist(path) in Save()
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <iterator>

#include <Core/Macros.hpp>
#include "INIFile.hpp"

namespace con {
INIFile::record_t::record_t( std::string _section, std::string _name, std::string _value ) :
	section( std::move( _section ) ),
	name( std::move( _name ) ),
	value( std::move( _value ) )
{}

bool INIFile::Open( const std::string& name )
{
	this->Clear();
	this->pathToFile = name;
	std::ifstream file( this->pathToFile );

	if ( !file )
		return false;

	std::string line = "";
	while ( !file.eof() ) {
		std::getline( file, line );
		if ( line.empty() ) // don't want empty lines
			continue;

		this->rawData.push_back( line );
	}

	return true;
}

bool INIFile::Save( const std::string& path, bool override )
{
	std::vector<std::string> serializeData;
	this->makeSerializeData( serializeData );

	if ( !path.empty() )
		this->pathToFile = path;

	if ( std::experimental::filesystem::exists( "./" + path ) &&
		 !override )
		return false;

	std::experimental::filesystem::remove( path );
	std::ofstream file( this->pathToFile );
	std::copy( serializeData.begin(), serializeData.end(), std::ostream_iterator<std::string>( file, "\n" ) );

	return true;
}

void INIFile::Parse()
{
	this->parsedData.clear();
	this->parsedData.reserve( this->rawData.size() );
	record_t tempRecord;
	std::string& section = tempRecord.section;
	std::string& name = tempRecord.name;
	std::string& value = tempRecord.value;
	std::string tempString;

	for ( const auto& str : this->rawData ) {
		if ( str.front() == ';' ) // ; - comment sign
			continue;

		tempString = str;
		// Removing blank spaces before name and after value (   name = value   )
		//													  ^^^            ^^^
		while ( tempString.front() == ' ' )
			tempString.erase( tempString.begin() );
		while ( tempString.back() == ' ' )
			tempString.pop_back();

		if ( tempString.find_first_of( '=' ) == std::string::npos ) // If there is no '=' then parse as Section
			section = parseAsSection( tempString );
		else {
			name = str.substr( 0, str.find_first_of( '=' ) );
			value = str.substr( str.find_first_of( '=' ) + 1 );

			// Removing blank after before name and before value (name   =   value)
			//														  ^^^ ^^^
			while ( name.back() == ' ' )
				name.pop_back();
			while ( value.front() == ' ' )
				value.erase( value.begin() );

			this->parsedData.push_back( tempRecord );
		}
	}

	this->parsedData.shrink_to_fit();
}

void INIFile::Clear()
{
	this->rawData.clear();
	this->parsedData.clear();
}

std::string INIFile::GetValue( const std::string& section, const std::string& name ) const
{
	// Redundancy here because I want to have 'const' getter.
	auto result = std::find_if( this->parsedData.begin(), this->parsedData.end(),
								[section, name]( auto& record )
	{
		return ( record.section == section ) && ( record.name == name );
	} );

	if ( result != this->parsedData.end() )
		return result->value;

	return std::string( "" );
}

std::string* INIFile::GetValuePtr( const std::string& section, const std::string& name )
{
	auto result = std::find_if( this->parsedData.begin(), this->parsedData.end(),
								[section, name]( auto& record )
	{
		return ( record.section == section ) && ( record.name == name );
	} );

	if ( result != this->parsedData.end() )
		return &result->value;

	return nullptr;
}

std::vector<INIFile::record_t> INIFile::GetParsedData()
{
	return this->parsedData;
}

std::vector<INIFile::record_t>& INIFile::GetParsedDataRef()
{
	return this->parsedData;
}

void INIFile::AddValue( const std::string& section, const std::string& name, const std::string& value )
{
	this->parsedData.emplace_back( section, name, value );
}

std::string INIFile::parseAsSection( const std::string& str )
{
	CON_ASSERT( str.front() == '[' && str.back() == ']', "missing or wrong section parenthssis" );

	// Starting from 1 for '['; -1 for \0 and -1 for ']'
	return str.substr( 1, str.size() - 1 - 1 );
}

void INIFile::makeSerializeData( std::vector<std::string>& to )
{
	to.clear();
	to.reserve( this->parsedData.size() );

	std::string section = "";
	for ( const auto& record : this->parsedData ) {
		if ( record.section != section ) {
			if ( section.empty() ) // If it's first section name then don't add '\n' at the beginning
				to.push_back( '[' + record.section + "]" );
			else
				to.push_back( "\n[" + record.section + "]" );

			section = record.section;
		}

		to.push_back( record.name + " = " + record.value );
	}
}
}