#include "ResourceManager.hpp"

#include <map>
#include <string>
#include <iostream>

ResourceManager::ResourceManager()
{
	std::cout << "ResourceManager created." << std::endl;
}

ResourceManager::~ResourceManager()
{
	freeAll();

	std::cout << "ResourceManager deconstructed." << std::endl;
}

sf::Texture* ResourceManager::loadTexture(const std::string& resourceName, const std::string& fileLocation)
{
	if (!isTextureLoaded(resourceName))
	{
		sf::Texture* new_tex = new sf::Texture;
		new_tex->loadFromFile(fileLocation);
		loadedTextures[resourceName] = new_tex;

		std::cout << "Loaded texture\"" + resourceName + "\" from \"" + fileLocation + "\"" << std::endl;

		return new_tex;
	}
}

bool ResourceManager::isTextureLoaded(const std::string& resourceName)
{
	if (loadedTextures.find(resourceName) == loadedTextures.end())
		return false;
	else
		return true;
}

sf::Texture* ResourceManager::getTexture(const std::string& resourceName)
{
	return loadedTextures[resourceName];
}

sf::Font* ResourceManager::loadFont(const std::string& resourceName, const std::string& fileLocation)
{
	if (!isFontLoaded(resourceName))
	{
		sf::Font* new_tex = new sf::Font;
		new_tex->loadFromFile(fileLocation);
		loadedFonts[resourceName] = new_tex;

		std::cout << "Loaded font\"" + resourceName + "\" from \"" + fileLocation + "\"" << std::endl;

		return new_tex;
	}
}

bool ResourceManager::isFontLoaded(const std::string& resourceName)
{
	if (loadedFonts.find(resourceName) == loadedFonts.end())
		return false;
	else
		return true;
}

sf::Font* ResourceManager::getFont(const std::string& resourceName)
{
	return loadedFonts[resourceName];
}

void ResourceManager::free(const std::string& resourceName)
{
	delete loadedTextures[resourceName];
	loadedTextures[resourceName] = nullptr;
	loadedTextures.erase(resourceName);
}

void ResourceManager::freeAll()
{
	for (auto& texture : loadedTextures)
	{
		delete loadedTextures[texture.first];
		loadedTextures[texture.first] = nullptr;
		loadedTextures.erase(texture.first);
	}

	for (auto& fonts : loadedFonts)
	{
		delete loadedFonts[fonts.first];
		loadedFonts[fonts.first] = nullptr;
		loadedFonts.erase(fonts.first);
	}

	std::cout << "Freed all resources." << std::endl;
}
