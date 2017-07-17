/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <vector>

#include <Core/ecs/Component.hpp>
#include <Core/Macros.hpp>
#include <Core/ecs/Functions.hpp>
#include <Core/components/Script.hpp>
#include <Core/Conversions.hpp>

namespace con {
// Forward declaration.
class EntityManager;

/*
===============================================================================
Created by: Condzi
	Main class of Entity Component System. To delete Entity use 'Kill' method.
	If you want to deactivate Entity (if is inactive then Rendering and other systems
	won't update its state.

===============================================================================
*/
class Entity final
{
public:
	explicit Entity( EntityManager& manager );

	bool IsAlive() const;
	bool IsActive() const;
	const componentBitset_t& GetComponentBitset() const;

	void Kill();
	void SetActive( bool val );

	template <typename T>
	bool HasComponent() const;
	template <typename T>
	T& GetComponent() const;

	template <typename T, typename... TArgs>
	T& AddComponent( TArgs&&... args );
	template <typename T, typename... TArgs>
	T& AddScriptComponent( Context& context, TArgs&& ...args );

	bool HasGroup( const groupID_t group ) const;
	void AddGroup( const groupID_t group );
	void RemoveGroup( const groupID_t group );

private:
	bool alive = true;
	bool active = true;
	componentArray_t componentArray;
	componentBitset_t componentBitset;
	groupBitset_t groupBitset;
	std::vector<std::unique_ptr<Component>> components;
	EntityManager* entityManager;

};

#include <Core/ecs/Entity.inl>
}