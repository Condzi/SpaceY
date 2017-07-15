/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <valarray>

#include <Core/state/State.hpp>
#include <Core/time/Clock.hpp>

namespace con {
/*
===============================================================================
Created by: Condzi
	When pushed prints simple debug data. (for now only Average FPS count)

===============================================================================
*/
class DebugDataState final :
	public State
{
public:
	DebugDataState( StateStack& stack, Context& cont ) :
		State( stack, cont )
	{}

	stateID_t GetID() const override
	{
		return (stateID_t)coreStates_t::DEBUG_DATA;
	}

	void Update() override
	{
		this->avgFPS.resize( this->avgFPS.size() + 1, Time::FRAME_TIME.AsSeconds() );

		if ( this->debugUpdateClock.GetEleapsedTime() >= asSeconds( 0.2f ) ) {
			LOG( "++++ DEBUG DATA ++++", INFO, CONSOLE );
			LOG( "Average FPS: " << 1 / ( this->avgFPS.sum() / this->avgFPS.size() ), INFO, CONSOLE );
			LOG( "---- DEBUG DATA ----", INFO, CONSOLE );
			this->debugUpdateClock.Restart();
			this->avgFPS.resize( 0 );
		}
	}

private:
	Clock debugUpdateClock;
	std::valarray<float> avgFPS;
};
}