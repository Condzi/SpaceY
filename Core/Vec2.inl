template<typename T>
inline sf::Vector2<T> con::Vec2<T>::AsSFMLVec() const
{
	return sf::Vector2<T>( this->x, this->y );
}

template<typename T>
inline std::string con::Vec2<T>::AsString() const
{
	return std::string( "Vec2( " + std::to_string( this->x ) + " | " + std::to_string( this->y ) + " )" );
}

template <typename T>
inline T Vec2<T>::Length() const
{
	// Calculate for nice precission, then cast if smaller is needed.
	return static_cast<T>( std::sqrtf( this->x * this->x + this->y * this->y ) );
}

template <typename T>
inline T con::Vec2<T>::LengthSquared() const
{
	return this->x * this->x + this->y * this->y;
}

template<typename T>
inline T con::Vec2<T>::DistanceSquared( const Vec2<T>& first, const Vec2<T>& second )
{
	return std::pow( second.x - first.x, 2 ) + std::pow( second.y - first.y, 2 );
}

template<typename T>
inline T con::Vec2<T>::Distance( const Vec2<T>& first, const Vec2<T>& second )
{
	return std::sqrt( con::Vec2<T>::DistanceSquared( first, second ) );
}

template<typename T>
inline Vec2<T> con::Vec2<T>::GetAbs() const
{
	return Vec2<T>( static_cast<T>( std::fabs( this->x ) ), static_cast<T>( std::fabs( this->y ) ) );
}

template<typename T>
inline T con::Vec2<T>::GetMin() const
{
	return std::min( this->x, this->y );
}

template<typename T>
inline T con::Vec2<T>::GetMax() const
{
	return std::max( this->x, this->y );
}

template <typename T>
template <typename Y>
inline T Vec2<T>::DotProduct( const Vec2<Y>& second ) const
{
	return this->x * second.x + this->y * second.y;
}

template <typename T>
template <typename Y>
inline T con::Vec2<T>::CrossProduct( const Vec2<Y>& second ) const
{
	return this->x * second.x - this->y * second.y;
}


template<typename T>
inline Vec2<T> con::Vec2<T>::operator-() const
{
	return Vec2<T>( -this->x, -this->y );
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator+( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x + second.x, this->y + second.y );
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator-( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x - second.x, this->y - second.y );
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator*( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x * second.x, this->y * second.y );
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator/( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x / second.x, this->y / second.y );
}


template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator+( const Y value ) const
{
	return Vec2<T>( this->x + value, this->y + value );
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator-( const Y value ) const
{
	return Vec2<T>( this->x - value, this->y - value );
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator*( const Y value ) const
{
	return Vec2<T>( this->x * value, this->y * value );
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator/( const Y value ) const
{
	return Vec2<T>( this->x / value, this->y / value );
}


template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator+=( const Vec2<Y>& second )
{
	this->x += static_cast<T>( second.x ); this->y += static_cast<T>( second.y );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator-=( const Vec2<Y>& second )
{
	this->x -= static_cast<T>( second.x ); this->y -= static_cast<T>( second.y );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator*=( const Vec2<Y>& second )
{
	this->x *= static_cast<T>( second.x ); this->y *= static_cast<T>( second.y );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator/=( const Vec2<Y>& second )
{
	this->x /= static_cast<T>( second.x ); this->y /= static_cast<T>( second.y );
	return *this;
}


template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator+=( const Y value )
{
	this->x += static_cast<T>( value ); this->y += static_cast<T>( value );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator-=( const Y value )
{
	this->x -= static_cast<T>( value ); this->y -= static_cast<T>( value );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator*=( const Y value )
{
	this->x *= static_cast<T>( value ); this->y *= static_cast<T>( value );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T> con::Vec2<T>::operator/=( const Y value )
{
	this->x /= static_cast<T>( value ); this->y /= static_cast<T>( value );
	return *this;
}


template<typename T>
template<typename Y>
inline bool con::Vec2<T>::operator==( const Vec2<Y>& second ) const
{
	return this->x == static_cast<T>( second.x ) && this->y == static_cast<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool con::Vec2<T>::operator!=( const Vec2<Y>& second ) const
{
	return this->x != static_cast<T>( second.x ) && this->y != static_cast<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool con::Vec2<T>::operator<( const Vec2<Y>& second ) const
{
	return this->x < static_cast<T>( second.x ) && this->y < static_cast<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool con::Vec2<T>::operator>( const Vec2<Y>& second ) const
{
	return this->x > static_cast<T>( second.x ) && this->y > static_cast<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool con::Vec2<T>::operator<=( const Vec2<Y>& second ) const
{
	return this->x <= static_cast<T>( second.x ) && this->y <= static_cast<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool con::Vec2<T>::operator>=( const Vec2<Y>& second ) const
{
	return this->x >= static_cast<T>( second.x ) && this->y >= static_cast<T>( second.y );
}


template<typename T>
inline Vec2<T> operator+( const T left, const Vec2<T>& right )
{
	return right + left;
}

template<typename T>
inline Vec2<T> operator-( const T left, const Vec2<T>& right )
{
	return right - left;
}

template<typename T>
inline Vec2<T> operator*( const T left, const Vec2<T>& right )
{
	return right * left;
}

template<typename T>
inline Vec2<T> operator/( const T left, const Vec2<T>& right )
{
	return right / left;
}