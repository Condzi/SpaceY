template <typename T>
inline Message<T>* Messenger::AddMessage( messageID_t id, const T& data )
{
	this->messages.emplace_back( std::make_unique<Message<T>>( id, data, this->messages.size() ) );
	return reinterpret_cast<Message<T>*>( this->messages.back().get() );
}

template<typename T>
inline Message<T>* Messenger::GetUniqueMessage( messageID_t id )
{
	auto result = this->findMessage( id );
	if ( result != this->messages.end() )
		return reinterpret_cast<Message<T>*>( ( *result ).get() );

	return nullptr;
}

template<typename T>
inline std::vector<Message<T>*> Messenger::GetAllMessages( messageID_t id )
{
	std::vector<Message<T>*> vec;
	vec.reserve( this->messages.size() );

	for ( auto& message : this->messages )
		if ( message && message->id == id )
			vec.push_back( reinterpret_cast<Message<T>*>( ( message.get() ) ) );

	return vec;
}
