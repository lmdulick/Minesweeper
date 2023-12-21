// FILEPATHS.CPP

#include "FilePaths.h"
unordered_map<string, sf::Texture> FilePaths::textureMap;

// add .png and files/images/ to filenames and load the texture with that new path
void FilePaths::LoadWithPath(const char* fname) {
	string filePath = "files/images/";
	filePath += fname;
	filePath += ".png";
	textureMap[fname].loadFromFile(filePath);
}

// get texture for Sprites
sf::Texture& FilePaths::FindTexture(const char* spriteName) {
	if (textureMap.find(spriteName) == textureMap.end()) {
		LoadWithPath(spriteName);
	}
	return textureMap[spriteName];
}

// clear the map
void FilePaths::Clear() {
	textureMap.clear();
}