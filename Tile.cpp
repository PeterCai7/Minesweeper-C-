#include "Tile.h"
#include <SFML/Graphics.hpp>
using namespace std;

Tile::Tile(int x, int y, int isMineOrNot) {
	this->x = x;
	this->y = y;
	if (isMineOrNot)
	{
		this->isAMine = true;
	}
	else {
		this->isAMine = false;
	}
	this->isRevealed = false;
	this->numOfNearbyMines = 0;
}

void Tile::Reveal() {
	if (this->isRevealed)
	{ 
		return;
	}
	this->isRevealed = true;
	// if (this->isAMine) {
	// 	this->numOfNearbyMines = -1;
	// }
	if (this->numOfNearbyMines == 0) {
		for (Tile* tile : this->adjacentTiles)
		{
			tile->Reveal();
		}
	}
}
