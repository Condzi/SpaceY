/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Core/Logger/Logger.hpp>
#include <Core/resourceManaging/ResourceWrapper.hpp>
#include <Core/Config.hpp>

namespace con
{
	using textureResource_t = ResourceWrapper<sf::Texture>;
	using fontResource_t = ResourceWrapper<sf::Font>;
	using uiTextResource_t = ResourceWrapper<sf::Text>;

	/*
	===============================================================================
	Created by: Condzi
		Resource Holder struct is created for resource managing. To add resources
		use public vectors. For deleting use specified DeleteAll... methods. To get
		resource, use Get... methods.

	===============================================================================
	*/
	struct ResourceHolder final
	{
		std::vector<std::unique_ptr<textureResource_t>> textures;
		std::vector<std::unique_ptr<uiTextResource_t>> uiTexts;
		std::vector<std::unique_ptr<fontResource_t>> fonts;

		textureResource_t* GetTexture( const resourceID_t id ) const;
		uiTextResource_t* GetText( const resourceID_t id ) const;
		fontResource_t* GetFont( const resourceID_t id ) const;

		void DeleteAllResources();
		void DeleteAllResourcesByPriority( const resourcePriorityID_t priority );
		void DeleteAllResourcesByID( const resourceID_t id );
	};
}