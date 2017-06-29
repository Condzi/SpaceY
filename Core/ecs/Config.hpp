/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <array>
#include <bitset>
#include <cinttypes>

namespace con
{
	// Forward declaration.
	struct Component;

	constexpr size_t MAX_COMPONENTS = 64;
	constexpr size_t MAX_GROUPS = 32;

	typedef std::bitset<MAX_COMPONENTS> componentBitset_t;
	typedef std::array<Component*, MAX_COMPONENTS> componentArray_t;
	typedef std::bitset<MAX_GROUPS> groupBitset_t;
	typedef size_t componentID_t;
	typedef uint8_t systemID_t;
	typedef uint8_t entityID_t;
	typedef uint8_t groupID_t;
}