/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/time/Clock.hpp>

namespace con
{
	Time Clock::GetEleapsedTime()
	{
		std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
		return Time( std::chrono::duration_cast<std::chrono::microseconds>( endTime - this->startTime ).count() );
	}

	Time Clock::Restart()
	{
		std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
		Time eleapsed = std::chrono::duration_cast<std::chrono::microseconds>( endTime - this->startTime ).count();

		this->startTime = std::chrono::steady_clock::now();

		return eleapsed;
	}
}
