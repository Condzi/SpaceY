/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/
#pragma once

#include <cinttypes>
#include <thread>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Stores Time as Milliseconds, Microseconds and seconds. Has declaration of
		Sleep function.

	===============================================================================
	*/
	class Time final
	{
		friend bool operator==( const Time& left, const Time& right );
		friend bool operator!=( const Time& left, const Time& right );
		friend bool operator<( const Time& left, const Time& right );
		friend bool operator>( const Time& left, const Time& right );
		friend bool operator<=( const Time& left, const Time& right );
		friend bool operator>=( const Time& left, const Time& right );
		friend Time& operator+( Time& left, const Time& right );
		friend Time& operator-( Time& left, const Time& right );
		friend Time& operator*( Time& left, const Time& right );
		friend Time& operator/( Time& left, const Time& right );

		friend Time asSeconds( const float val );
		friend Time asMilliseconds( const int32_t val );
		friend Time asMicroseconds( const int64_t& val );
		friend void SleepFor( const Time& time );

	public:
		static Time FRAME_TIME;

		Time::Time( int64_t microseconds = 0 ) :
			microseconds( std::move( microseconds ) )
		{}

		float AsSeconds() const;
		int32_t AsMilliseconds() const;
		int64_t AsMicroseconds() const;

		Time& operator=( const Time& other );
		Time& operator+=( const Time& other );
		Time& operator-=( const Time& other );
		Time& operator*=( const Time& other );
		Time& operator/=( const Time& other );

	protected:
		// 1 second - 1 000 000 microseconds
		// 1 millisecond - 1 000 microseconds
		int64_t microseconds;
	};
	;
}

