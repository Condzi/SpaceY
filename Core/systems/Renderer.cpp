#include <Core/state/State.hpp>
#include <Core/ecs/EntityManager.hpp>
#include <Core/Vec2.hpp>
#include <Core/systems/Renderer.hpp>

namespace con
{
	void Renderer::Update()
	{
		this->updateView();
		auto window = this->context.window;
		window->setView( this->view );

		auto drawables = this->getDrawables();

		window->clear();
		auto drawLayersInterval = this->getDrawLayersInterval( drawables );
		size_t entitiesAlreadyDrawn = 0;
		for (
			int8_t currentLayer = drawLayersInterval.first;
			( currentLayer < drawLayersInterval.second + 1 && entitiesAlreadyDrawn < drawables.size() );
			currentLayer++
			)
		{
			for ( auto drawable : drawables )
				if ( drawable->drawLayer == currentLayer )
				{
					window->draw( drawable->sprite );
					entitiesAlreadyDrawn++;
				}
		}
		window->display();
	}

	std::vector<DrawableComponent*> Renderer::getDrawables()
	{
		auto entities = this->context.entityManager->GetEntitiesWithSignature( this->signature );
		std::vector<DrawableComponent*> drawables;
		drawables.reserve( entities.size() );

		for ( auto entity : entities )
			if ( entity->IsActive() && entity->IsAlive() )
				drawables.push_back( &entity->GetComponent<DrawableComponent>() );

		return drawables;
	}

	std::pair<int8_t, int8_t> Renderer::getDrawLayersInterval( const std::vector<DrawableComponent*>& drawables ) const
	{
		int8_t min = INT8_MAX, max = INT8_MIN;

		for ( auto drawable : drawables )
		{
			auto currentLayer = drawable->drawLayer;

			if ( currentLayer > max ) max = currentLayer;
			if ( currentLayer < min ) min = currentLayer;
		}

		return std::pair<int8_t, int8_t>( min, max );
	}

	void Renderer::updateView()
	{
		const Vec2i designed = { this->context.settings->GetInt( "WINDOW", "DESIGNED_X" ), this->context.settings->GetInt( "WINDOW", "DESIGNED_Y" ) };
		this->view = this->context.window->getDefaultView();
		this->view.reset( { 0.0f,0.0f, (float)designed.x, (float)designed.y } );
	}
}