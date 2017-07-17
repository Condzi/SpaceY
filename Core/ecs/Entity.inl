template<typename T>
inline bool con::Entity::HasComponent() const
{
	CON_STATIC_ASSERT( std::is_base_of_v<Component, T>, 
					   "T must inherit from Component" );
	return this->componentBitset[getComponentTypeID<T>()];
}

template<typename T>
inline T& con::Entity::GetComponent() const
{
	CON_ASSERT( this->HasComponent<T>(), 
				"Entity doesn't have component of id " + 
				To<std::string>( getComponentTypeID<T>() ) );

	auto ptr( this->componentArray[getComponentTypeID<T>()] );
	return *reinterpret_cast<T*>( ptr );
}

template<typename T, typename ...TArgs>
inline T& con::Entity::AddComponent( TArgs && ...args )
{
	CON_STATIC_ASSERT( std::is_base_of_v<Component, T>, 
					   "T must inherit from Component" );
	CON_ASSERT( !this->HasComponent<T>(), 
				"Entity already has component of id " +
				To<std::string>( getComponentTypeID<T>() ) );

	std::unique_ptr<Component> component = std::make_unique<T>( std::forward<TArgs>( args )... );
	Component* rawPtr = component.get();

	this->components.emplace_back( std::move( component ) );

	this->componentArray[getComponentTypeID<T>()] = rawPtr;
	this->componentBitset[getComponentTypeID<T>()] = true;

	rawPtr->entity = this;
	rawPtr->Init();
	return *reinterpret_cast<T*>( rawPtr );
}

template<typename T, typename ...TArgs>
inline T& con::Entity::AddScriptComponent( Context & context, TArgs && ...args )
{
	CON_STATIC_ASSERT( std::is_base_of_v<ScriptComponent, T>, 
					   "T must inherit from ScriptComponent" );
	CON_ASSERT( !this->HasComponent<T>(), 
				"Entity already has component of id " + 
				To<std::string>( getComponentTypeID<T>() ) );

	std::unique_ptr<Component> component = std::make_unique<T>( std::forward<TArgs>( args )... );
	Component* rawPtr = component.get();

	this->components.emplace_back( std::move( component ) );

	this->componentArray[getComponentTypeID<T>()] = rawPtr;
	this->componentBitset[getComponentTypeID<T>()] = true;

	rawPtr->entity = this;

	reinterpret_cast<T*>( rawPtr )->context = context;
	rawPtr->Init();
	return *reinterpret_cast<T*>( rawPtr );
}

