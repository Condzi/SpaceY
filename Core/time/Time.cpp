/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/time/Time.hpp>

namespace con
{
	Time Time::FRAME_TIME = 0;

	bool operator==( const Time& left, const Time& right )
	{
		return left.microseconds == right.microseconds;
	}
	bool operator!=( const Time& left, const Time& right )
	{
		return !( left == right );
	}
	bool operator<( const Time& left, const Time& right )
	{
		return left.microseconds < right.microseconds;
	}
	bool operator>( const Time& left, const Time& right )
	{
		return left.microseconds > right.microseconds;
	}

	bool operator<=( const Time& left, const Time& right )
	{
		return left.microseconds <= right.microseconds;
	}

	bool operator>=( const Time& left, const Time& right )
	{
		return left.microseconds >= right.microseconds;
	}

	Time asSeconds( const float val )
	{
		return static_cast<int64_t>( val * 1000000 );
	}

	Time asMilliseconds( const int32_t val )
	{
		return static_cast<int64_t>( val ) * 1000;
	}

	Time asMicroseconds( const int64_t& val )
	{
		return val;
	}

	Time& operator+( Time& left, const Time& right )
	{
		left += right;
		return left;
	}
	Time& operator-( Time& left, const Time& right )
	{
		left -= right;
		return left;
	}
	Time& operator*( Time& left, const Time& right )
	{
		left *= right;
		return left;
	}
	Time& operator/( Time& left, const Time& right )
	{
		left /= right;
		return left;
	}

	float Time::AsSeconds() const
	{
		return this->microseconds / 1000000.f;
	}

	int32_t Time::AsMilliseconds() const
	{
		return static_cast<int32_t>( this->microseconds / 1000 );
	}

	int64_t Time::AsMicroseconds() const
	{
		return this->microseconds;
	}

	Time& Time::operator=( const Time& other )
	{
		this->microseconds = other.microseconds;
		return *this;
	}

	void SleepFor( const Time& time )
	{
		std::this_thread::sleep_for( std::chrono::microseconds( time.microseconds ) );
	}

	Time& Time::operator+=( const Time& other )
	{
		this->microseconds += other.microseconds;
		return *this;
	}

	Time& Time::operator-=( const Time& other )
	{
		this->microseconds -= other.microseconds;
		return *this;
	}

	Time& Time::operator*=( const Time& other )
	{
		this->microseconds *= other.microseconds;
		return *this;
	}

	Time& Time::operator/=( const Time& other )
	{
		this->microseconds /= other.microseconds;
		return *this;
	}
}
