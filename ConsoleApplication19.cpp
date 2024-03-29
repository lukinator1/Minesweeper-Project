// ConsoleApplication16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Tile.h"
#include "Board.h"
#include <vector>
#include <unordered_map>
using namespace std;
using namespace sf;
bool CheckWinCondition(Tile tilearray[]);
int main()
{
	RenderWindow window(VideoMode(800, 600), "Minesweeper");
	Board board;
	board.DrawBoard(window);
	window.display();
	bool playeralive = true;
	bool wincondition = false;
	sf::Event event;
	sf::Mouse mouse;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (CheckWinCondition(board.tiles) == true) {
				window.clear();
				board.Victory();
				board.DrawBoard(window);
				window.display();
				playeralive = false;
			}
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


					if (playeralive == true) {
						for (int i = 0; i < 400; i++) {
		/*tile pressing*/		if ((mouse.getPosition(window).x > board.tiles[i].tilesprite.getPosition().x) && (mouse.getPosition(window).x <= board.tiles[i].tilesprite.getPosition().x + 32) && (mouse.getPosition(window).y > board.tiles[i].tilesprite.getPosition().y) && (mouse.getPosition(window).y <= board.tiles[i].tilesprite.getPosition().y + 32)) {
								window.clear();
								board.tiles[i].Reveal(window, playeralive);
								if (playeralive == false) {
									board.GameOver();   //display gameover board
								}
								board.DrawBoard(window);
								window.display();
							}
						}
	/*debug button*/	if (mouse.getPosition(window).x >= board.debugsprite.getPosition().x && mouse.getPosition(window).x <= (board.debugsprite.getPosition().x + 64) && mouse.getPosition(window).y >= board.debugsprite.getPosition().y && mouse.getPosition(window).y <= (board.debugsprite.getPosition().y + 64)) {
							window.clear();
							board.RevealMines(window);
							board.DrawBoard(window);
							window.display();
						}

	/*test 1*/			if ((mouse.getPosition(window).x > board.test1sprite.getPosition().x) && (mouse.getPosition(window).x <= board.test1sprite.getPosition().x + 64) && (mouse.getPosition(window).y > board.test1sprite.getPosition().y) && (mouse.getPosition(window).y <= board.test1sprite.getPosition().y + 64)) {
							window.clear();
							board.ClearBoard();
							board.LoadTest(1);
							board.DrawBoard(window);
							window.display();
						}
	/*test 2*/			if ((mouse.getPosition(window).x > board.test2sprite.getPosition().x) && (mouse.getPosition(window).x <= board.test2sprite.getPosition().x + 64) && (mouse.getPosition(window).y > board.test2sprite.getPosition().y) && (mouse.getPosition(window).y <= board.test2sprite.getPosition().y + 64)) {
							window.clear();
							board.ClearBoard();
							board.LoadTest(2);
							board.DrawBoard(window);
							window.display();
						}
					}

	/*smile button */	if (mouse.getPosition(window).x >= board.smilesprite.getPosition().x && mouse.getPosition(window).x <= (board.smilesprite.getPosition().x + 64) && mouse.getPosition(window).y >= board.smilesprite.getPosition().y && mouse.getPosition(window).y <= (board.smilesprite.getPosition().y + 64)) {
						window.clear();
						board.ResetGame(window, playeralive);
						board.DrawBoard(window);
						window.display();
					}				
				}


	/*flagging*/		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (playeralive == true) {
					for (int i = 0; i < 400; i++) {
						if ((mouse.getPosition(window).x > board.tiles[i].tilesprite.getPosition().x) && (mouse.getPosition(window).x <= board.tiles[i].tilesprite.getPosition().x + 32) && (mouse.getPosition(window).y > board.tiles[i].tilesprite.getPosition().y) && (mouse.getPosition(window).y <= board.tiles[i].tilesprite.getPosition().y + 32)) {
							window.clear();
							board.tiles[i].Flag(board.scoreboard, board.totalminecount);
							board.DrawBoard(window);
							window.display();
						}
					}
				}
			}
		}
	}
}
bool CheckWinCondition(Tile tilearray[]) {
	bool won = true;
	for (int i = 0; i < 400; i++) {
		if (tilearray[i].isrevealed == false && tilearray[i].ismine == false) {
			won = false;
		}
	}
	return won;
}