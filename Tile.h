#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Tile
{
public:
	void Reveal(RenderWindow &window, bool &playeralive);
	void Explode(RenderWindow &window);
	void Flag(int &scoreboard, int &boardtotalminecount);
	Sprite tilesprite;
	Texture tiletexture;
	Tile *neighbors[8];
	int adjacentmines;
	bool ismine;
	bool isrevealed;
	bool minerevealed;
	bool flagged;
	bool edgetile;
	bool cornertile;
	Tile();
	~Tile();
};

