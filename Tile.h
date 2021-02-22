#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
using namespace std;
class Tile {
private:
	int x;
	int y;
public:
	int numOfNearbyMines;
	std::vector<Tile*> adjacentTiles;
	bool isAMine;
	sf::Sprite sprite;
	bool isRevealed;
	Tile(int x, int y, int isMineOrNot);
	void Reveal();
};

#endif