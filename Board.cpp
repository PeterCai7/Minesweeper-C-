#include <SFML/Graphics.hpp>
#include<fstream>
#include<iostream>
#include<curses.h>
#include <string>

#include "Board.h"
#include "Tile.h"
using namespace std;

Board::Board(const string& filePath){
	this->numMines = 0;
    this->numRevealed = 0;
    //initialize?
    ifstream ifile;
    // cout << filePath << endl;
    // cout << &filePath << endl;
    ifile.open(filePath,ios::in);
    if (!ifile)
    {
        cout << "Board loading failed" << endl;
        return;
    }
    // else {
    //     cout << "Board loading succeed" << endl;
    // }
    int m = 25;
    int n = 16;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int isAMine;
            char c;
            ifile >> c;
            isAMine = c - 48;
            // if( j == m - 1)
            //     cout << isAMine << endl;
            // else
            //     cout << isAMine;
            if(isAMine)
                this->numMines++;
            this->board[j][i] = new Tile(i, j, isAMine);
        }
    }
    ifile.close();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            this->findAdjacentTiles(i, j);
        }
    }
}

void Board::findAdjacentTiles(int x, int y) {
    if(this->board[x][y]->adjacentTiles.size() == 0) {
        int deltaX[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int deltaY[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        for (int i = 0; i < 8; ++i)
        {
            int new_x = x + deltaX[i];
            int new_y = y + deltaY[i];
            if(new_x >= 0 && new_x < 25 && new_y >=0 && new_y < 16) {
                this->board[x][y]->adjacentTiles.push_back(board[new_x][new_y]);
            }
        }    
    }
    //cout << "one findAdjacentTiles() called" << endl;
	
    this->board[x][y]->numOfNearbyMines = 0;
    for(Tile* tile : this->board[x][y]->adjacentTiles) {
        if(tile->isAMine) {
            this->board[x][y]->numOfNearbyMines++;
        }
    }
}