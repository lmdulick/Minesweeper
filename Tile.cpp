// TILE.CPP

#include "Tile.h"




// constructor (creates tile_hidden tile)
Tile::Tile() {
	SetSprite("tile_hidden");
	tfMine = false;
	tfOpen = false;
	tfFlag = false;
}

sf::Sprite& Tile::GetSprite() {
	return this->tile;
}

void Tile::SetSprite(const char* spriteName) {
	this->tile.setTexture(FilePaths::FindTexture(spriteName));
}

void Tile::SetPosition(float x, float y) {
	this->GetSprite().setPosition(x, y);
}

// open tile if there isn't a flag
void Tile::RevealTile() {
	if (!this->TF_Flag()) {
		this->SetSprite("tile_revealed");
		this->tfOpen = true;
	}
}

void Tile::SetMine() {
	this->tfMine = true;
}

void Tile::RevealNeighbors() {
	if (this != nullptr && this->CheckNeighborMines() == 0 && !this->TF_Mine() && !this->TF_Flag()) {
		for (int i = 0; i < 8; i++) {
			if (this->neighbors[i] != nullptr) {
				if (!this->neighbors[i]->TF_Open() && !this->neighbors[i]->TF_Mine() && !this->TF_Flag()) {
					this->neighbors[i]->RevealTile();
					if (this->neighbors[i]->CheckNeighborMines() == 0) {
						this->neighbors[i]->RevealNeighbors();
					}
				}
			}
		}
	}
}

void Tile::SetFlag() {
	this->tfFlag = true;
}

void Tile::EraseFlag() {
	this->tfFlag = false;
}

void Tile::ResetTile() {
	this->SetSprite("tile_hidden");
	this->tfOpen = false;
	tfMine = false;
	tfFlag = false;
}

void Tile::SwitchReveal()
{
	this->tfReveal = !tfReveal;
}

bool Tile::TF_Mine() {
	if (this->tfMine) {
		return true;
	}
	else {
		return false;
	}
}

bool Tile::TF_Open() {
	if (this->tfOpen) {
		return true;
	}
	return false;
}

bool Tile::TF_Flag() {
	if (this->tfFlag) {
		return true;
	}
	else {
		return false;
	}
}

bool Tile::TF_Reveal()
{
	return tfReveal;
}

int Tile::CheckNeighborMines() {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		if (this->neighbors[i] != nullptr) {
			if (this->neighbors[i]->TF_Mine())
				count++;
		}
	}
	return count;
}













