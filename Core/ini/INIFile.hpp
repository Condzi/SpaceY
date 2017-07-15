/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <string>
#include <vector>

namespace con {

// TODO: Add comments.
class INIFile final
{
	struct record_t
	{
		std::string section, name, value;
		record_t( std::string _section = "", std::string _name = "", std::string _value = "" );
	};

public:
	bool Open( const std::string& path );
	bool Save( const std::string& path = "", bool override = true );
	void Parse();
	void Clear();

	std::string GetValue( const std::string& section, const std::string& name ) const;
	std::string* GetValuePtr( const std::string& section, const std::string& name );
	std::vector<record_t> GetParsedData();
	std::vector<record_t>& GetParsedDataRef();
	void AddValue( const std::string& section, const std::string& name, const std::string& value );

private:
	std::string pathToFile = "";
	std::vector<std::string> rawData;
	std::vector<record_t> parsedData;

	std::string parseAsSection( const std::string& str );
	void makeSerializeData( std::vector<std::string>& to );
};
}