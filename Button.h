// BUTTON.H

#pragma once
#include <SFML/Graphics.hpp>
#include "FilePaths.h"

class Button {
public:
	Button(const char* buttonName);
	sf::Sprite button;
	void SetSprite(const char* buttonName);
	void SetPosition(float x, float y);
	sf::Sprite& GetSprite();
};