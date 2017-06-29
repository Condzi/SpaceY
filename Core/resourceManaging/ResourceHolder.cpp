/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <Core/resourceManaging/ResourceHolder.hpp>

namespace con
{
	textureResource_t* ResourceHolder::GetTexture( const resourceID_t id ) const
	{
		for ( auto& ptr : this->textures )
			if ( ptr->GetResourceID() == id )
				return ptr.get();

		LOG( "Cannot find Texture of ID " << +id, ERROR, BOTH );
		return nullptr;
	}

	uiTextResource_t* ResourceHolder::GetText( const resourceID_t id ) const
	{
		for ( auto& ptr : this->uiTexts )
			if ( ptr->GetResourceID() == id )
				return ptr.get();

		LOG( "Cannot find Text of ID " << +id, ERROR, BOTH );
		return nullptr;
	}

	fontResource_t* ResourceHolder::GetFont( const resourceID_t id ) const
	{
		for ( auto& ptr : this->fonts )
			if ( ptr->GetResourceID() == id )
				return ptr.get();

		LOG( "Cannot find Font of ID " << +id, ERROR, BOTH );
		return nullptr;
	}

	void ResourceHolder::DeleteAllResources()
	{
		LOG( "Starting to delete all resources...", INFO, BOTH );
		LOG( this->textures.size() << " Textures", INFO, BOTH );
		this->textures.clear();
		LOG( this->uiTexts.size() << " Texts", INFO, BOTH );
		this->uiTexts.clear();
		LOG( this->fonts.size() << " Fonts", INFO, BOTH );
		this->fonts.clear();
		LOG( "All resources deleted!", INFO, BOTH );
	}

	void ResourceHolder::DeleteAllResourcesByPriority( const resourcePriorityID_t priority )
	{
		LOG( "Starting to delete all resources of priority " << +priority, INFO, BOTH );

		uint16_t counter = 0;

		for ( auto textureIterator = this->textures.begin(); textureIterator != this->textures.end(); )
		{
			if ( ( *textureIterator )->GetResourcePriority() == priority )
			{
				textureIterator = this->textures.erase( textureIterator );
				counter++;
			} else
				textureIterator++;
		}
		for ( auto textsIterator = this->uiTexts.begin(); textsIterator != this->uiTexts.end(); )
		{
			if ( ( *textsIterator )->GetResourcePriority() == priority )
			{
				textsIterator = this->uiTexts.erase( textsIterator );
				counter++;
			} else
				textsIterator++;
		}
		for ( auto fontIterator = this->fonts.begin(); fontIterator != this->fonts.end(); )
		{
			if ( ( *fontIterator )->GetResourcePriority() == priority )
			{
				fontIterator = this->fonts.erase( fontIterator );
				counter++;
			} else
				fontIterator++;
		}

		LOG( counter << " resources of priority " << +priority << " deleted", INFO, BOTH );
	}

	void ResourceHolder::DeleteAllResourcesByID( const resourceID_t id )
	{
		LOG( "Starting to delete all resources of ID " << +id, INFO, BOTH );

		uint16_t counter = 0;

		for ( auto textureIterator = this->textures.begin(); textureIterator != this->textures.end(); )
		{
			if ( ( *textureIterator )->GetResourceID() == id )
			{
				textureIterator = this->textures.erase( textureIterator );
				counter++;
			} else
				textureIterator++;
		}
		for ( auto textsIterator = this->uiTexts.begin(); textsIterator != this->uiTexts.end(); )
		{
			if ( ( *textsIterator )->GetResourceID() == id )
			{
				textsIterator = this->uiTexts.erase( textsIterator );
				counter++;
			} else
				textsIterator++;
		}
		for ( auto fontIterator = this->fonts.begin(); fontIterator != this->fonts.end(); )
		{
			if ( ( *fontIterator )->GetResourceID() == id )
			{
				fontIterator = this->fonts.erase( fontIterator );
				counter++;
			} else
				fontIterator++;
		}

		LOG( counter << " resources of ID " << +id << " deleted", INFO, BOTH );
	}
}