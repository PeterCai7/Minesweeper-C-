#include <SFML/Graphics.hpp>
#include<fstream>
#include<iostream>
#include<curses.h>
#include <string>
#include "Board.h"
#include "Tile.h"
#include "Helper.h"
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    Helper help;
    sf::Sprite painter;
    //setting auxiliary buttons
    sf::Sprite counter;
    counter.setTexture(help.digits);
    

    sf::Sprite face;
    face.setTexture(help.happy);
    face.setPosition(11 * 32 + 16, 16 * 32);

    sf::Sprite debug_button;
    debug_button.setTexture(help.debug);
    debug_button.setPosition(15 * 32 + 16, 16 * 32);

    sf::Sprite test1;
    test1.setTexture(help.t1);
    test1.setPosition(17 * 32 + 16, 16 * 32);

    sf::Sprite test2;
    test2.setTexture(help.t2);
    test2.setPosition(19 * 32 + 16, 16 * 32);

    sf::Sprite test3;
    test3.setTexture(help.t3);
    test3.setPosition(21 * 32 + 16, 16 * 32);

    string board1 = "./boards/testboard1.brd";
    string board2 = "./boards/testboard2.brd";
    string board3 = "./boards/testboard3.brd";
    string board0 = "./boards/testboard0.brd";
    help.loadingBoard(board0);
    help.randomize();
    //setting sprites on the board
    help.settingSprites();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // if (event.type == sf::Event::MouseMoved) {
            //     cout << "new mouse x: " << event.mouseMove.x << std::endl;
            //     cout << "new mouse y: " << event.mouseMove.y << std::endl;
            // }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "the left button was pressed" << endl;
                    cout << "out mouse x: " << event.mouseButton.x << endl;
                    cout << "out mouse y: " << event.mouseButton.y << endl;
                    if(help.isOnTest1(event.mouseButton.x, event.mouseButton.y)) {
                        help.loadingBoard(board1);
                        help.settingSprites();
                        face.setTexture(help.happy);
                        cout << "b1" << endl;
                    }
                    else if(help.isOnTest2(event.mouseButton.x, event.mouseButton.y)) {
                        help.loadingBoard(board2);
                        help.settingSprites();
                        face.setTexture(help.happy);
                        cout << "b2" << endl;
                    }
                    else if(help.isOnTest3(event.mouseButton.x, event.mouseButton.y)) {
                        help.loadingBoard(board3);
                        help.settingSprites();
                        face.setTexture(help.happy);
                        cout << "b3" << endl;
                    }
                    else if(help.isOnFace(event.mouseButton.x, event.mouseButton.y)) {
                        help.loadingBoard(board0);
                        help.randomize();
                        help.settingSprites();
                        face.setTexture(help.happy);
                    }
                    else if(!help.GameOver && help.isOnDebug(event.mouseButton.x, event.mouseButton.y)) {
                        help.displayMines();
                    }
                    else if(!help.GameOver && help.isOnBoard(event.mouseButton.x, event.mouseButton.y)) {
                        if(!help.GameOver)
                            help.reveal(event.mouseButton.x, event.mouseButton.y);
                        if(help.GameOver) {
                            if(help.LoseTheGame) {
                                face.setTexture(help.lose);
                            }
                            else if(help.WinTheGame) {
                                face.setTexture(help.win);
                            }
                        }
                    }

                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    cout << "the right button was pressed" << endl;
                    if(!help.GameOver && help.isOnBoard(event.mouseButton.x, event.mouseButton.y)) {
                        // cout << "Right clicked on the board" << endl;
                        help.displayFlag(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }
        }
        window.clear(sf::Color(255, 255, 255, 0));
        for(int i = 0; i < 25; i++) {
	    	for(int j = 0; j < 16; j++) {
	    		if(help.boardObj->board[i][j]->isRevealed) {
	    			painter.setPosition(i * 32, j * 32);
	    			painter.setTexture(help.tile_revealed);
	    			window.draw(painter);
	    		}
	    		else {
	    			if(help.sprite_2D[i][j]->getTexture() == &help.flag) {
	    				painter.setPosition(i * 32, j * 32);
		    			painter.setTexture(help.tile_hidden);
		    			window.draw(painter);
	    			}
	    			if(help.sprite_2D[i][j]->getTexture() == &help.mine) {
	    				painter.setPosition(i * 32, j * 32);
		    			if(help.GameOver) {
		    				painter.setTexture(help.tile_revealed);
		    			}
		    			else {
		    				painter.setTexture(help.tile_hidden);
		    			}
		    			window.draw(painter);
	    			}
	    		}
	    		window.draw(*help.sprite_2D[i][j]);
	    	}
	    }
	    // drawing the counter
	    int n = 0;
	    int count = help.boardObj->numMines - help.numFlags;
	    if(count < 0) {
	    	counter.setPosition((n++) * 21, 16 * 32);
	    	counter.setTextureRect(help.digit_minus);
	    	window.draw(counter);
	    	count = 0 - count;
	    }
	    // hundreds
	    counter.setPosition((n++) * 21, 16 * 32);
	    counter.setTextureRect(help.choseRect(count / 100));
	    window.draw(counter);
	    // tens
	    count = count - (count / 100) * 100;
	    counter.setPosition((n++) * 21, 16 * 32);
	    counter.setTextureRect(help.choseRect(count / 10));
	    window.draw(counter);
        // ones
        count = count - (count / 10) * 10;
	    counter.setPosition((n++) * 21, 16 * 32);
	    counter.setTextureRect(help.choseRect(count));
	    window.draw(counter);

        window.draw(face);
        window.draw(debug_button);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.display();
    }

    return 0;
}


