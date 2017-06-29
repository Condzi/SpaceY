#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <Core/components/Drawable.hpp>
#include <Core/ecs/System.hpp>
#include <Core/ecs/Functions.hpp>
#include <Core/logger/Logger.hpp>
#include <Core/Settings.hpp>

namespace con
{
	/*
	===============================================================================
	Created by: Condzi
		Renderer uses a component blocks of DrawableCompoents. You should get them
		using Reserve method in ecs::World. Pass them directly here. Don't
		clear or display using sf::RenderWindow* in Context, Game class will handle
		everything.

	===============================================================================
	*/
	class Renderer final :
		public System
	{
	public:
		Renderer( Context cont ) :
			System( std::move( cont ) )
		{}

		void Init() override
		{
			this->signature = createComponentSignature( getComponentTypeID<DrawableComponent>() );
		}

		systemID_t GetID() const override
		{
			return 3;
		}

		void Update() override;

	private:
		componentBitset_t signature;
		sf::View view;

		std::vector<DrawableComponent*> getDrawables();
		std::pair<int8_t, int8_t> getDrawLayersInterval( const std::vector<DrawableComponent*>& drawables ) const;
		// Call when resizing a window.
		void updateView();
	};
}