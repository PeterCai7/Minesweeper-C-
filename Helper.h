#ifndef HELPER_H
#define HELPER_H
#include<fstream>
#include<iostream>
#include<curses.h>
#include <SFML/Graphics.hpp>
#include <string>
class Board;
using namespace std;
class Helper {
public:
	sf::Texture tile_hidden;
    sf::Texture tile_revealed;
    sf::Texture mine;
    sf::Texture flag;
    sf::Texture digits;
    sf::Texture debug;
    sf::Texture happy;
    sf::Texture lose;
    sf::Texture win;
    sf::Texture t1;
    sf::Texture t2;
    sf::Texture t3;
    sf::Texture one;
    sf::Texture two;
    sf::Texture three;
    sf::Texture four;
    sf::Texture five;
    sf::Texture six;
    sf::Texture seven;
    sf::Texture eight;
    const sf::IntRect digit_0 = sf::IntRect(0, 0, 21, 32);
    const sf::IntRect digit_1 = sf::IntRect(21, 0, 21, 32);
    const sf::IntRect digit_2 = sf::IntRect(42, 0, 21, 32);
    const sf::IntRect digit_3 = sf::IntRect(63, 0, 21, 32);
    const sf::IntRect digit_4 = sf::IntRect(84, 0, 21, 32);
    const sf::IntRect digit_5 = sf::IntRect(105, 0, 21, 32);
    const sf::IntRect digit_6  = sf::IntRect(126, 0, 21, 32);
    const sf::IntRect digit_7 = sf::IntRect(147, 0, 21, 32);
    const sf::IntRect digit_8  = sf::IntRect(168, 0, 21, 32);
    const sf::IntRect digit_9 = sf::IntRect(189, 0, 21, 32);
    const sf::IntRect digit_minus = sf::IntRect(210, 0, 21, 32);

    Board *boardObj;
    sf::Sprite *sprite_2D[25][16];
    int numFlags;

    bool debugModeOpen;
    bool GameOver;
    bool WinTheGame;
    bool LoseTheGame;

	Helper();
	bool isOnTest1(int x, int y);
	bool isOnTest2(int x, int y);
	bool isOnTest3(int x, int y);
    bool isOnFace(int x, int y);
    bool isOnDebug(int x, int y);
    bool isOnBoard(int x, int y);

    void loadingBoard(const string& filePath);
    void randomize();
    void settingSprites();
    void displayMines();
    void displayFlag(int x, int y);
    void reveal(int x, int y);
    void loseGame();
    void updateRevealedTiles();
    void winGame();
    const sf::IntRect choseRect(int c);
};


#endif