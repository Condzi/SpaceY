/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <vector>
#include <memory>

#include <Core/state/State.hpp>
#include <Core/systems/Renderer.hpp>

namespace con
{
	class StateStack final
	{
		enum class action_t : uint8_t
		{
			POP,
			PUSH
		};

		struct pendingAction_t final
		{
			action_t action;
			stateID_t state;

			pendingAction_t( const action_t act, const stateID_t stat = EXIT_STATE );
		};

	public:
		void SetContext( Context cont )
		{
			this->context = std::move( cont );
		}

		template <typename T, typename... TArgs>
		void RegisterState( const stateID_t id, TArgs&&... args )
		{
			CON_STATIC_ASSERT( std::is_base_of_v<State, T>, "Must derive from State class" );
			this->factories[id] = [&]
			{
				return std::make_unique<T>( *this, this->context, std::forward<TArgs>( args )... );
			};
		}

		void ApplyPendingActions();
		void Update();

		void Pop()
		{
			this->pendingActions.emplace_back( action_t::POP );
		}
		void Push( const stateID_t id )
		{
			this->pendingActions.emplace_back( action_t::PUSH, std::move( id ) );
		}
		// Returns STATE_EXIT if no states on stack.
		stateID_t GetStateOnTop()
		{
			if ( this->stack.empty() )
				return EXIT_STATE;

			return this->stack.back()->GetID();
		}

	private:
		std::vector<std::unique_ptr<State>> stack;
		std::vector<pendingAction_t> pendingActions;
		std::unordered_map<stateID_t, std::function<std::unique_ptr<State>()>> factories;
		Context context;

		std::unique_ptr<State> createState( const stateID_t id );
	};
}
