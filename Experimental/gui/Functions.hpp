/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Text.hpp>

#include <Core/Conversions.hpp>

namespace con {

// Solution from Nexus's proposal: https://en.sfml-dev.org/forums/index.php?topic=7174
inline Vec2f getCorrectTextBounds( const sf::Text& text )
{
	const sf::String str = text.getString() + '\n';

	float maxLineWidth = 0.f;
	float lineWidth = 0.f;
	unsigned int lines = 0;

	for ( const auto& itr : str ) {
		if ( itr == '\n' ) {
			++lines;
			maxLineWidth = std::max( maxLineWidth, lineWidth );
			lineWidth = 0.f;
		} else
			lineWidth += text.getFont()->getGlyph( itr, text.getCharacterSize(), text.getStyle() & sf::Text::Bold ).advance;
	}

	const auto lineHeight = To<float>( text.getFont()->getLineSpacing( text.getCharacterSize() ) );
	return { maxLineWidth, lines * lineHeight };
}

// From texus's TGUI
inline uint32_t findBestTextSize( const sf::Font& font, float height, int32_t fit )
{
	if ( height < 2 )
		return 1;

	std::vector<uint32_t> textSizes( To<size_t>( height ) );
	for ( uint32_t i = 0; i < To<uint32_t>( height ); i++ )
		textSizes[i] = i + 1;

	auto high = std::lower_bound( textSizes.begin(), textSizes.end(), height,
								  [&font]( uint32_t charSize, float h )
	{
		return font.getLineSpacing( charSize ) < h;
	} );
	if ( high == textSizes.end() )
		return To<uint32_t>( height );

	float highLineSpacing = font.getLineSpacing( *high );
	if ( highLineSpacing == height )
		return To<uint32_t>( height );

	auto low = high - 1;
	float lowLineSpacing = font.getLineSpacing( *low );

	if ( fit < 0 )
		return *low;
	else if ( fit > 0 )
		return *high;
	else {
		if ( std::abs( height - lowLineSpacing ) <
			 std::abs( height - highLineSpacing ) )
			return *low;
		else
			return *high;
	}
}
}