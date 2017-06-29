#include <Core/state/State.hpp>
#include <Core/state/StateStack.hpp>

namespace con
{
	Context::Context( Game* g ) :
		game( g )
	{}

	void State::StartThread()
	{
		if ( this->threadRunning )
			this->StopThread();

		this->threadRunning = true;
		this->thread = std::thread( &State::threadloop, this );
	}

	void State::StopThread()
	{
		if ( !this->threadRunning )
			return;

		this->threadRunning = false;
		this->thread.join();
	}

	void State::requestStackPush( const stateID_t id )
	{
		this->stateStack.Push( std::move( id ) );
	}

	void State::requestStackPop()
	{
		this->stateStack.Pop();
	}

	bool State::imStateOnTopOfTheStack()
	{
		return this->stateStack.GetStateOnTop() == this->GetID();
	}

	stateID_t State::getStateOnTopOfTheStack()
	{
		return this->stateStack.GetStateOnTop();
	}

	void State::threadloop()
	{
		while ( this->threadRunning )
			this->UpdateThread();
	}
}