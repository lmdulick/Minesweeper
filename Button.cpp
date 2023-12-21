// BUTTON.CPP

#include "Button.h"
#include "FilePaths.h"

// constructor for ALL buttons
Button::Button(const char* buttonName) {
	SetSprite(buttonName);
}

void Button::SetSprite(const char* buttonName) {
	this->button.setTexture(FilePaths::FindTexture(buttonName));
}

void Button::SetPosition(float x, float y) {
	this->GetSprite().setPosition(x, y);
}

sf::Sprite& Button::GetSprite() {
	return this->button;
}