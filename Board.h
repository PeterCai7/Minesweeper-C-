#ifndef BOARD_H
#define BOARD_H
#include<fstream>
#include<iostream>
#include<curses.h>
#include <string>
class Tile;
using namespace std;
class Board {
public:
	int numRevealed;
    int numMines;
	Tile *board[25][16];
	Board(const string& filePath);
	void findAdjacentTiles(int x, int y);
};


#endif