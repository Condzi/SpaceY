/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <vector>

#include <Core/ecs/Component.hpp>
#include <Core/Assert.hpp>
#include <Core/ecs/Functions.hpp>
#include <Core/components/Script.hpp>

namespace con
{
	// Forward declaration.
	class EntityManager;

	/*
	===============================================================================
	Created by: Condzi
		Main class of Entity Component System. To delete Entity use 'Kill' method.
		If you want to deactivate Entity (if is inactive then Renderingand other systems
		won't update its state.

	===============================================================================
	*/
	class Entity final
	{
	public:
		explicit Entity( EntityManager& manager ) :
			alive( true ),
			active( true ),
			entityManager( &manager )
		{}

		bool IsAlive() const
		{
			return this->alive;
		}
		void Kill()
		{
			if ( this->HasComponent<ScriptComponent>() )
				this->GetComponent<ScriptComponent>().OnKill();

			this->alive = false;
		}
		bool IsActive() const
		{
			return this->active;
		}
		void SetActive( bool val )
		{
			if ( val != this->active )
				if ( !val )
				{
					if ( this->HasComponent<ScriptComponent>() )
						this->GetComponent<ScriptComponent>().OnSleep();
					else
						if ( this->HasComponent<ScriptComponent>() )
							this->GetComponent<ScriptComponent>().OnActive();
				}

			this->active = val;
		}

		template <typename T>
		bool HasComponent() const
		{
			CON_STATIC_ASSERT( std::is_base_of_v<Component, T>, "T must inherit from Component" );
			return this->componentBitset[getComponentTypeID<T>()];
		}

		const componentBitset_t& GetComponentBitset() const
		{
			return this->componentBitset;
		}

		template <typename T, typename... TArgs>
		T& AddComponent( TArgs&&... args )
		{
			CON_STATIC_ASSERT( std::is_base_of_v<Component, T>, "T must inherit from Component" );
			CON_ASSERT( !this->HasComponent<T>(), "Entity already has component of id " + std::to_string( getComponentTypeID<T>() ) );

			std::unique_ptr<Component> component = std::make_unique<T>( std::forward<TArgs>( args )... );
			Component* rawPtr = component.get();

			this->components.emplace_back( std::move( component ) );

			this->componentArray[getComponentTypeID<T>()] = rawPtr;
			this->componentBitset[getComponentTypeID<T>()] = true;

			rawPtr->entity = this;
			rawPtr->Init();
			return *reinterpret_cast<T*>( rawPtr );
		}

		template <typename T, typename... TArgs>
		T& AddScriptComponent( Context& context, TArgs&& ...args )
		{
			CON_STATIC_ASSERT( std::is_base_of_v<ScriptComponent, T>, "T must inherit from ScriptComponent" );
			CON_ASSERT( !this->HasComponent<T>(), "Entity already has component of id " + std::to_string( getComponentTypeID<T>() ) );

			std::unique_ptr<Component> component = std::make_unique<T>( std::forward<TArgs>( args )... );
			Component* rawPtr = component.get();

			this->components.emplace_back( std::move( component ) );

			this->componentArray[getComponentTypeID<T>()] = rawPtr;
			this->componentBitset[getComponentTypeID<T>()] = true;

			rawPtr->entity = this;

			reinterpret_cast<T*>( rawPtr )->context = &context;
			rawPtr->Init();
			return *reinterpret_cast<T*>( rawPtr );
		}


		template <typename T>
		T& GetComponent() const
		{
			CON_ASSERT( this->HasComponent<T>(), "Entity doesn't have component of id " + std::to_string( +getComponentTypeID<T>() ) );

			auto ptr( this->componentArray[getComponentTypeID<T>()] );
			return *reinterpret_cast<T*>( ptr );
		}

		bool HasGroup( const groupID_t group ) const
		{
			return this->groupBitset[group];
		}

		void AddGroup( const groupID_t group );
		void RemoveGroup( const groupID_t group )
		{
			this->groupBitset[group] = false;
		}

	private:
		bool alive;
		bool active;
		componentArray_t componentArray;
		componentBitset_t componentBitset;
		groupBitset_t groupBitset;
		std::vector<std::unique_ptr<Component>> components;
		EntityManager* entityManager;

	};
}