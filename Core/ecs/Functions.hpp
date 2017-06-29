/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/ecs/Config.hpp>
#include <Core/Assert.hpp>
#include <Core/components/Script.hpp>

namespace con
{
	namespace internal
	{
		inline componentID_t getUniqueComponentID() noexcept
		{
			static componentID_t lastID = 0u;
			return lastID++;
		}

		template <typename T>
		inline componentID_t _getComponentTypeID()
		{
			CON_STATIC_ASSERT( std::is_base_of_v<Component, T>, "T must inherit from Component" );

			static componentID_t typeID = internal::getUniqueComponentID();
			return typeID;
		}
	}

	/*
	====================
	Created by: Condzi
	getComponentTypeID<T>
		Returns unique id of component type (T).
	====================
	*/
	template <typename T>
	inline componentID_t getComponentTypeID() noexcept
	{
		if ( std::is_base_of_v<ScriptComponent, T> )
			return internal::_getComponentTypeID<ScriptComponent>();

		return internal::_getComponentTypeID<T>();
	}

	/*
	====================
	Created by: Condzi
	createComponentSignature
		Generates component signature that can be passed to EntityManager to get
		Entity with specified components.
	====================
	*/
	template <typename... TArgs>
	inline auto createComponentSignature( const componentID_t first, TArgs&&... args )
	{
		componentBitset_t bitset;
		std::vector<componentID_t> rest { std::forward<TArgs>( args )... };

		bitset[first] = true;
		for ( auto arg : rest )
			bitset[arg] = true;

		return bitset;
	}
}