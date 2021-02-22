#include "Helper.h"
#include "Board.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
using namespace std;

Helper::Helper() {

	// loading all textures needed
    if (!this->tile_hidden.loadFromFile("./images/tile_hidden.png")) {
    	cout<<"loading tile_hidden failed";
    }
    if (!this->tile_revealed.loadFromFile("./images/tile_revealed.png")) {
    	cout<<"loading tile_revealed failed";
    }
    if (!this->mine.loadFromFile("./images/mine.png")) {
    	cout<<"loading mine failed";
    }
    
    if (!this->flag.loadFromFile("./images/flag.png")) {
    	cout<<"loading flag failed";
    }
    
    if (!this->digits.loadFromFile("./images/digits.png")) {
        cout<<"loading digits failed";
    }
    
    if (!this->debug.loadFromFile("./images/debug.png")) {
        cout<<"loading debug failed";
    }
    
    if (!this->happy.loadFromFile("./images/face_happy.png")) {
        cout<<"loading happy failed";
    }
    
    if (!this->lose.loadFromFile("./images/face_lose.png")) {
        cout<<"loading lose failed";
    }
    
    if (!this->win.loadFromFile("./images/face_win.png")) {
        cout<<"loading win failed";
    }
    // loading numbers
    
    if (!this->one.loadFromFile("./images/number_1.png")) {
        cout<<"loading one failed";
    }
    
    if (!this->two.loadFromFile("./images/number_2.png")) {
        cout<<"loading two failed";
    }
    
    if (!this->three.loadFromFile("./images/number_3.png")) {
        cout<<"loading three failed";
    }
    
    if (!this->four.loadFromFile("./images/number_4.png")) {
        cout<<"loading four failed";
    }
    
    if (!this->five.loadFromFile("./images/number_5.png")) {
        cout<<"loading five failed";
    }
    
    if (!this->six.loadFromFile("./images/number_6.png")) {
        cout<<"loading six failed";
    }
    
    if (!this->seven.loadFromFile("./images/number_7.png")) {
        cout<<"loading seven failed";
    }
    
    if (!this->eight.loadFromFile("./images/number_8.png")) {
        cout<<"loading eight failed";
    }

    //loading tests
    
    if (!this->t1.loadFromFile("./images/test_1.png")) {
        cout<<"loading t1 failed";
    }
    
    if (!this->t2.loadFromFile("./images/test_2.png")) {
        cout<<"loading t2 failed";
    }
    
    if (!this->t3.loadFromFile("./images/test_3.png")) {
        cout<<"loading t3 failed";
    }

    this->debugModeOpen = false;
    this->GameOver = false;
    this->WinTheGame = false;
    this->LoseTheGame = false;

    this->numFlags = 0;
}

bool Helper::isOnTest1(int x, int y){ 
	return x > 17 * 32 + 16 && x < 17 * 32 + 16 + 64 && y > 16 * 32 && y < 18 * 32;
}

bool Helper::isOnTest2(int x, int y){
	return x > 19 * 32 + 16 && x < 19 * 32 + 16 + 64 && y > 16 * 32 && y < 18 * 32;
}

bool Helper::isOnTest3(int x, int y){
	return x > 21 * 32 + 16 && x < 21 * 32 + 16 + 64 && y > 16 * 32 && y < 18 * 32;
}

bool Helper::isOnFace(int x, int y){
    return x > 11 * 32 + 16 && x < 11 * 32 + 16 + 64 && y > 16 * 32 && y < 18 * 32;
}

bool Helper::isOnDebug(int x, int y) {
    return x > 15 * 32 + 16 && x < 15 * 32 + 16 + 64 && y > 16 * 32 && y < 18 * 32;
}

bool Helper::isOnBoard(int x, int y) {
    return x > 0 && x < 25 * 32 && y > 0 && y < 16 * 32;
}

void Helper::loadingBoard(const string& filePath) {
    this->boardObj = new Board(filePath); 
    this->debugModeOpen = false;
    this->GameOver = false;
    this->LoseTheGame = false;
    this->WinTheGame = false;
    this->numFlags = 0;
}

void Helper::randomize() {
    srand(time(0));
    this->boardObj->numMines = 50;
    for (int n = 0; n < 50; ++n){
        int i = rand() % 25;
        int j = rand() % 16;
        if (this->boardObj->board[i][j]->isAMine)
        {
            n--;
        }
        else {
            this->boardObj->board[i][j]->isAMine = true;
        }
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 16; j++) {
            this->boardObj->findAdjacentTiles(i, j);
        }
    }
}

void Helper::settingSprites() {
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 16; j++) {
            this->sprite_2D[i][j] = &(this->boardObj->board[i][j]->sprite);
            // if(this->boardObj->board[i][j]->isAMine) 
            //     this->sprite_2D[i][j]->setTexture(this->mine);
            // else
            this->sprite_2D[i][j]->setTexture(this->tile_hidden);
            this->sprite_2D[i][j]->setPosition(i * 32, j * 32);
        }
    }
}

void Helper::displayMines() {
    if(!this->debugModeOpen) {
        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 16; j++) {
                if(this->boardObj->board[i][j]->isAMine) 
                    this->sprite_2D[i][j]->setTexture(this->mine);
            }
        }
    }
    else {
        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 16; j++) {
                if(this->boardObj->board[i][j]->isAMine) 
                    this->sprite_2D[i][j]->setTexture(this->tile_hidden);
            }
        }
    }
    this->debugModeOpen = !this->debugModeOpen;
}

void Helper::displayFlag(int x, int y) {
    int i = x / 32;
    int j = y / 32;
    if(this->sprite_2D[i][j]->getTexture() == &this->flag) {
        this->sprite_2D[i][j]->setTexture(this->tile_hidden);
        this->numFlags--;
    }
    else if (this->sprite_2D[i][j]->getTexture() == &this->tile_hidden)
    {
        this->sprite_2D[i][j]->setTexture(this->flag);
        this->numFlags++;
    }
}

void Helper::reveal(int x, int y) {
    int i = x / 32;
    int j = y / 32;
    if(this->sprite_2D[i][j]->getTexture() == &this->flag) {
        return;
    }
    if(this->boardObj->board[i][j]->isAMine) {
        this->loseGame();
        return;
    }
    
    this->boardObj->board[i][j]->Reveal();
    this->updateRevealedTiles();
    // cout << this->boardObj->numRevealed << endl;
    // cout << this->boardObj->numMines << endl;
    if(25 * 16 - this->boardObj->numRevealed == this->boardObj->numMines) {
        // cout << this->boardObj->numRevealed << endl;
        // cout << this->boardObj->numMines << endl;
        this->winGame();
    }
}

void Helper::updateRevealedTiles() {
    this->boardObj->numRevealed = 0;
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 16; j++) {
            if(this->boardObj->board[i][j]->isRevealed) {
                if(this->sprite_2D[i][j]->getTexture() == &this->flag) {
                    this->boardObj->board[i][j]->isRevealed = false;
                    cout << "reset works" << endl;
                    continue;
                }
                this->boardObj->numRevealed++;
                switch (this->boardObj->board[i][j]->numOfNearbyMines) {
                    case 0 : 
                        this->sprite_2D[i][j]->setTexture(this->tile_revealed);
                        break;
                    case 1 :
                        this->sprite_2D[i][j]->setTexture(this->one);
                        break;
                    case 2 :
                        this->sprite_2D[i][j]->setTexture(this->two);
                        break;
                    case 3 :
                        this->sprite_2D[i][j]->setTexture(this->three);
                        break;
                    case 4 :
                        this->sprite_2D[i][j]->setTexture(this->four);
                        break;
                    case 5 :
                        this->sprite_2D[i][j]->setTexture(this->five);
                        break;
                    case 6 :
                        this->sprite_2D[i][j]->setTexture(this->six);
                        break;
                    case 7 :
                        this->sprite_2D[i][j]->setTexture(this->seven);
                        break;
                    case 8 :
                        this->sprite_2D[i][j]->setTexture(this->eight);
                        break;
                    default :
                        break;
                }
            }
        }
    }
}

void Helper::loseGame() {
    this->GameOver = true;
    this->LoseTheGame = true;
    this->displayMines();
}

void Helper::winGame() {
    this->GameOver = true;
    this->WinTheGame = true;
}

const sf::IntRect Helper::choseRect(int c) {
    switch (c) {
        case 0 : 
            return this->digit_0;
            break;
        case 1 :
            return this->digit_1;
            break;
        case 2 :
            return this->digit_2;
            break;
        case 3 :
            return this->digit_3;
            break;
        case 4 :
            return this->digit_4;
            break;
        case 5 :
            return this->digit_5;
            break;
        case 6 :
            return this->digit_6;
            break;
        case 7 :
            return this->digit_7;
            break;
        case 8 :
            return this->digit_8;
            break;
        case 9 :
            return this->digit_9;
            break;
        default :
            return this->digit_0;
            break;
    }
}