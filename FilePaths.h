// FILEPATHS.H

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
using namespace std;


class FilePaths {
	static unordered_map<string, sf::Texture> textureMap;
	static void LoadWithPath(const char* fname);

public:
	static sf::Texture& FindTexture(const char* spriteName);
	static void Clear();
};