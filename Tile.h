// TILE.H

#pragma once
#include <SFML/Graphics.hpp>
#include "FilePaths.h"

class Tile {
	int mineNext;
	bool tfMine;
	bool tfOpen;
	bool tfFlag;
	bool tfReveal = false;

public:
	Tile();
	Tile* neighbors[8];

	sf::Sprite tile;
	sf::Sprite& GetSprite();

	void SetSprite(const char* spriteName);
	void SetPosition(float x, float y);
	void RevealTile();
	void SetMine();
	void RevealNeighbors();
	void SetFlag();
	void EraseFlag();
	void ResetTile();
	void SwitchReveal();

	bool TF_Mine();
	bool TF_Open();
	bool TF_Flag();
	bool TF_Reveal();

	int CheckNeighborMines();
};