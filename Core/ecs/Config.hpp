/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <array>
#include <bitset>
#include <cinttypes>

namespace con {
// Forward declaration.
struct Component;

constexpr size_t MAX_COMPONENTS = 64;
constexpr size_t MAX_GROUPS = 32;

using componentBitset_t = std::bitset<MAX_COMPONENTS>;
using componentArray_t = std::array<Component*, MAX_COMPONENTS>;
using groupBitset_t = std::bitset<MAX_GROUPS>;
using componentID_t = size_t;
using systemID_t = uint8_t;
using entityID_t = uint8_t;
using groupID_t = uint8_t;

using messageID_t = int8_t;
}