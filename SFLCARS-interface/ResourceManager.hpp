#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

// TODO: template resource class

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void setResourceDirectory(const std::string& directory);
	const std::string& getResourceDirectory() const;

	sf::Texture* loadTexture(const std::string& resourceName, const std::string& fileLocation);
	bool isTextureLoaded(const std::string& resourceName);
	sf::Texture* getTexture(const std::string& resourceName);

	sf::Font* loadFont(const std::string& resourceName, const std::string& fileLocation);
	bool isFontLoaded(const std::string& resourceName);
	sf::Font* getFont(const std::string& resourceName);

	void free(const std::string& resourceName);
	void freeAll();

private:
	std::map<std::string, sf::Texture*> loadedTextures;
	std::map<std::string, sf::Font*> loadedFonts;

	std::string basedir = "./resources/";
};

#endif
