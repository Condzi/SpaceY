/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/
#pragma once

#include <chrono>

#include <Core/time/Time.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Class created to counting time.

	===============================================================================
	*/
	class Clock
	{
	public:
		Clock() :
			startTime( std::chrono::steady_clock::now() )
		{}
		virtual ~Clock() {}

		Time GetEleapsedTime();
		Time Restart();

	protected:
		std::chrono::high_resolution_clock::time_point startTime;
	};
}


