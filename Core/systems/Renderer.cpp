#include <Core/ecs/EntityManager.hpp>
#include <Core/Vec2.hpp>
#include <Core/Context.hpp>
#include <Core/systems/Renderer.hpp>

namespace con {
void Renderer::Update()
{
	this->updateView();
	auto window = this->context.window;
	window->setView( this->view );

	auto drawables = this->getDrawables();
	std::sort( drawables.begin(), drawables.end(),
			   []( DrawableComponent* first, DrawableComponent* second )
	{
		return first->drawLayer < second->drawLayer;
	} );

	window->clear();
	for ( auto drawable : drawables )
		window->draw( *drawable->object.GetAsDrawable() );
	window->display();
}

std::vector<DrawableComponent*> Renderer::getDrawables()
{
	auto entities = this->context.entityManager->GetEntitiesWithSignature( this->signature );
	std::vector<DrawableComponent*> drawables;
	drawables.reserve( entities.size() );

	for ( auto entity : entities )
		if ( entity->IsActive() && entity->IsAlive() ) {
			auto drawable = &entity->GetComponent<DrawableComponent>();
			if ( drawable->object.GetAsDrawable() )
				drawables.push_back( drawable );
		}

	return drawables;
}

void Renderer::updateView()
{
	//const Vec2i designed = { this->context.settings->GetInt( "WINDOW", "DESIGNED_X" ), this->context.settings->GetInt( "WINDOW", "DESIGNED_Y" ) };
	const Vec2i designed( 1920, 1080 );
	this->view = this->context.window->getDefaultView();
	this->view.reset( { 0.0f,0.0f, (float)designed.x, (float)designed.y } );
}
}