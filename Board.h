#pragma once
#include "Tile.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Board : private Tile
{
public:
	Tile tiles[400];
	Sprite minesprite;
	Sprite flagsprite;
	Sprite digitssprite;
	Sprite debugsprite;
	Sprite test1sprite;
	Sprite test2sprite;
	Sprite smilesprite;
	Sprite numbersprite;
	Sprite boardhiddensprite;
	Sprite boardrevealedsprite;
	Sprite scoreboardsprites[3];
	Texture one;
	Texture two;
	Texture three;
	Texture four;
	Texture five;
	Texture six;
	Texture seven;
	Texture eight;
	Texture smiletexture;
	Texture minetexture;
	Texture flagtexture;
	Texture numbertexture;
	Texture digitstexture;
	Texture debugtexture;
	Texture test1texture;
	Texture test2texture;
	Texture boardrevealedtexture;
	Texture boardhiddentexture;
	Texture scoreboardtexture;
	void ResetGame(RenderWindow &window, bool &playerstatus);
	void DrawBoard(RenderWindow &window);
	void GameOver();
	void RevealMines(RenderWindow &window);
	void Victory();
	void LoadTest(int filenumber);
	void ClearBoard();
	int scoreboard;
	int totalminecount;
	bool gameover;
	Board();
	~Board();
};

