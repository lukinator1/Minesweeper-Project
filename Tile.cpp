#include "pch.h"
#include "Tile.h"
#include <iostream>
void Tile::Explode(RenderWindow &window) {
	minerevealed = true;
	isrevealed = true;
}
void Tile::Reveal(RenderWindow &window, bool &playeralive) {
	if (ismine == true) {
		Explode(window);
		playeralive = false;
		return;
	}
	if (isrevealed == true || flagged == true) {
		return;
	}
	isrevealed = true;
	if (adjacentmines == 0) {
		for (int i = 0; i < 8; i++) {
			if (neighbors[i] != nullptr) {
				neighbors[i]->Reveal(window, playeralive);
			}
		}
	}
}
void Tile::Flag(int &scoreboard, int &totalmines) {
	if (flagged == false && isrevealed == false) {
		if (scoreboard != 0) {
			scoreboard--;
			flagged = true;
		}
	}
	else if (flagged == true && isrevealed == false) {
		flagged = false;
		if (scoreboard < totalmines) {
			scoreboard++;
		}
	}
}
Tile::Tile()
{
	adjacentmines = 0;
	ismine = false;
	flagged = false;
	isrevealed = false;
	minerevealed = false;
	cornertile = false;
	edgetile = false;
}
Tile::~Tile()
{
}

















/*
int count = 0;
for (int i = 0; i < 8; i++) {
	if (neighbors[i] != nullptr) {
		if (neighbors[i]->ismine == true) {
			count++;
		}
	}
}
switch (count) {
case 0:
{
	for (int i = 0; i < 8; i++) {
		if (neighbors[i] != nullptr) {
				neighbors[i]->Reveal(window, playeralive);
		}
	break;
	}
	a = 0;
}
case 1:
	number = 1;
	break;
case 2:
	number = 2;
	break;
case 3:
	number = 3;
	break;
case 4:
	number = 4;
	break;
case 5:
	number = 5;
	break;
case 6:
	number = 6;
	break;
case 7:
	number = 7;
	break;
case 8:
	number = 8;
	break;
}*/