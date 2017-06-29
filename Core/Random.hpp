/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <random>
#include <ctime>

#include <Core/Assert.hpp>

namespace con
{
	// Namespace for randomizing functions.
	namespace Random
	{
		inline auto getRandomEngine() -> decltype( auto )
		{
			static std::mt19937 rndEngine( static_cast<uint32_t>( std::time( nullptr ) ) );
			return ( rndEngine );
		}

		inline float value( const float min, const float max )
		{
			if ( min == max )
				return min;

			CON_ASSERT( min < max, "Minimum random value must be smaller than maximum" );
			std::uniform_real_distribution<float> dist( min, max );
			return dist( getRandomEngine() );
		}

		inline int32_t value( const int32_t min, const int32_t max )
		{
			if ( min == max )
				return min;

			CON_ASSERT( min < max, "Minimum random value must be smaller than maximum" );
			std::uniform_int_distribution<int> dist( min, max );
			return dist( getRandomEngine() );
		}
	}
}