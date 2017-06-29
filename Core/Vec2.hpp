/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <algorithm>
#include <cmath>
#include <cinttypes>
// std::move
#include <utility>
// For fancy AsString method.
#include <string>

// Conversion to SFML type vector.
#include <SFML/System/Vector2.hpp>

namespace con
{
	template <typename T>
	struct Vec2;

	template <typename T>
	struct Vec2
	{
		T x, y;
		static const Vec2<T> Zero;
		static const Vec2<T> One;
		static const Vec2<T> Left;
		static const Vec2<T> Right;
		static const Vec2<T> Up;
		static const Vec2<T> Down;

		Vec2() :
			x( 0 ), y( 0 )
		{}
		Vec2( T xx, T yy ) :
			x( std::move( xx ) ),
			y( std::move( yy ) )
		{}
		template <typename Y>
		Vec2( Y xx, Y yy ) :
			x( std::move( static_cast<T>( xx ) ) ),
			y( std::move( static_cast<T>( yy ) ) )
		{}
		template <typename Y>
		Vec2( Vec2<Y> second ) :
			x( std::move( static_cast<T>( second.x ) ) ),
			y( std::move( static_cast<T>( second.y ) ) )
		{}
		// Making Vec2 polymorphic makes it bigger by 4 bytes. (polymorphic size: 12 bytes, non polymorphic - 8)
	#if !defined NO_POLYMORPHIC_VEC2
		virtual ~Vec2() {}
	#endif
		void Set( T xx, T yy )
		{
			this->x = std::move( xx );
			this->y = std::move( yy );
		}
		void Set( const Vec2<T>& second )
		{
			*this = second;
		}

		sf::Vector2<T> AsSFMLVec() const;
		std::string AsString() const;
		Vec2<T> GetAbs() const;
		T GetMin() const;
		T GetMax() const;

		T Length() const;
		T LengthSquared() const;
		template <typename Y>
		T DotProduct( const Vec2<Y>& second ) const;
		template <typename Y>
		T CrossProduct( const Vec2<Y>& second ) const;

		static T DistanceSquared( const Vec2<T>& first, const Vec2<T>& second );
		static T Distance( const Vec2<T>& first, const Vec2<T>& second );

		Vec2<T> operator-() const;

		template <typename Y>
		Vec2<T> operator+( const Vec2<Y>& second ) const;
		template <typename Y>
		Vec2<T> operator-( const Vec2<Y>& second ) const;
		template <typename Y>
		Vec2<T> operator*( const Vec2<Y>& second ) const;
		template <typename Y>
		Vec2<T> operator/( const Vec2<Y>& second ) const;

		template <typename Y>
		Vec2<T> operator+( const Y value ) const;
		template <typename Y>
		Vec2<T> operator-( const Y value ) const;
		template <typename Y>
		Vec2<T> operator*( const Y value ) const;
		template <typename Y>
		Vec2<T> operator/( const Y value ) const;

		template <typename Y>
		Vec2<T> operator+=( const Vec2<Y>& second );
		template <typename Y>
		Vec2<T> operator-=( const Vec2<Y>& second );
		template <typename Y>
		Vec2<T> operator*=( const Vec2<Y>& second );
		template <typename Y>
		Vec2<T> operator/=( const Vec2<Y>& second );

		template <typename Y>
		Vec2<T> operator+=( const Y value );
		template <typename Y>
		Vec2<T> operator-=( const Y value );
		template <typename Y>
		Vec2<T> operator*=( const Y value );
		template <typename Y>
		Vec2<T> operator/=( const Y value );

		template <typename Y>
		bool operator==( const Vec2<Y>& second ) const;
		template <typename Y>
		bool operator!=( const Vec2<Y>& second ) const;
		template <typename Y>
		bool operator<( const Vec2<Y>& second ) const;
		template <typename Y>
		bool operator>( const Vec2<Y>& second ) const;
		template <typename Y>
		bool operator<=( const Vec2<Y>& second ) const;
		template <typename Y>
		bool operator>=( const Vec2<Y>& second ) const;
	};

	template <typename T>
	const Vec2<T> Vec2<T>::Zero = Vec2<T>();
	template <typename T>
	const Vec2<T> Vec2<T>::One = Vec2<T>( 1, 1 );
	template <typename T>
	const Vec2<T> Vec2<T>::Left = Vec2<T>( -1, 0 );
	template <typename T>
	const Vec2<T> Vec2<T>::Right = Vec2<T>( 1, 0 );
	template <typename T>
	const Vec2<T> Vec2<T>::Up = Vec2<T>( 0, 1 );
	template <typename T>
	const Vec2<T> Vec2<T>::Down = Vec2<T>( 0, -1 );

	template <typename T>
	Vec2<T> operator+( const T left, const Vec2<T>& right );
	template <typename T>
	Vec2<T> operator-( const T left, const Vec2<T>& right );
	template <typename T>
	Vec2<T> operator*( const T left, const Vec2<T>& right );
	template <typename T>
	Vec2<T> operator/( const T left, const Vec2<T>& right );

#include <Core/Vec2.inl>

	typedef Vec2<float> Vec2f;
	typedef Vec2<int32_t> Vec2i;
	typedef Vec2<uint32_t> Vec2u;
}