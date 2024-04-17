#include "AssetLoader.h"

AssetLoader::AssetLoader()
{
}

void AssetLoader::loadAssets(const std::string& filePath)
{
	std::fstream file;
	file.open(filePath, std::ios::in); // read
	if (file.fail())
	{
		std::cout << "File fail to read!!";
		return;
	}
	std::string assetType;
	while (file >> assetType)
	{
		std::string name;
		std::string path;
		file >> name >> path;
		//std::cout << "type: " << assetType << " name: " << name << " path: " << path << std::endl;
		if (assetType == "texture")
		{
			// texture load
			sf::Texture texture;
			if (!texture.loadFromFile(path))
			{
				// error...
				std::cout << "Fail to load texture!! path: " << path << std::endl;
			}
			texture.setSmooth(true);
			m_textures[name] = texture;
		}
		else if (assetType == "font")
		{
			sf::Font font;
			if (!font.loadFromFile(path))
			{
				// error...
				std::cout << "Fail to load font!! path: " << path << std::endl;
			}
			m_fonts[name] = font;
		}
	}
}

sf::Font& AssetLoader::getFont(const std::string& name)
{
	if (m_fonts.find(name) == m_fonts.end())
	{
		// no key found
		std::cout << "Font not fount!!" << std::endl;
		sf::Font font;
		return font;
	}
	else
	{
		return m_fonts.at(name);
	}
}

sf::Texture& AssetLoader::getTexture(const std::string& name)
{
	if (m_textures.find(name) == m_textures.end())
	{
		// no key found
		std::cout << "Texture not fount!!" << std::endl;
		sf::Texture t;
		return t;
	}
	else
	{
		return m_textures.at(name);
	}
}
