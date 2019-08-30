#include <string>
#include <sstream>
#include "pch.h"
#include "Board.h"
using namespace sf;
using namespace std;
void Board::DrawBoard(RenderWindow &window) {
	int counter = 0;
	for (int i = 0; i <= 480; i += 32) {  //draw tiles
		for (int u = 0; u <= 768; u += 32) {
			tiles[counter].tilesprite.setPosition(sf::Vector2f(u, i));
			numbersprite.setPosition(tiles[counter].tilesprite.getPosition());
			flagsprite.setPosition(tiles[counter].tilesprite.getPosition());
			minesprite.setPosition(tiles[counter].tilesprite.getPosition());
			if (tiles[counter].isrevealed == true) {
				tiles[counter].tilesprite.setTexture(boardrevealedtexture);
				window.draw(tiles[counter].tilesprite);
				if (tiles[counter].ismine == false) {
					switch (tiles[counter].adjacentmines) {
					case 0:
						break;
					case 1:
						numbersprite.setTexture(one);
						window.draw(numbersprite);
						break;
					case 2:
						numbersprite.setTexture(two);
						window.draw(numbersprite);
						break;
					case 3:
						numbersprite.setTexture(three);
						window.draw(numbersprite);
						break;
					case 4:
						numbersprite.setTexture(four);
						window.draw(numbersprite);
						break;
					case 5:
						numbersprite.setTexture(five);
						window.draw(numbersprite);
						break;
					case 6:
						numbersprite.setTexture(six);
						window.draw(numbersprite);
						break;
					case 7:
						numbersprite.setTexture(seven);
						window.draw(numbersprite);
						break;
					case 8:
						numbersprite.setTexture(eight);
						window.draw(numbersprite);
						break;
					}
				}
			}
			else {
				tiles[counter].tilesprite.setTexture(boardhiddentexture);
				window.draw(tiles[counter].tilesprite);
			}
		if (tiles[counter].minerevealed == true) {
				window.draw(minesprite);
			}
		if (tiles[counter].flagged == true) {
				window.draw(flagsprite);
			}
			counter++;
		}
	}
	string scorestring = to_string(scoreboard);
	if (scorestring.length() == 1) {
		scorestring = "00" + scorestring;
	}
	else if (scorestring.length() == 2) {
		scorestring = "0" + scorestring;
	}
	for (int i = 0; i < 3; i++) {     //scoreboard 
		switch (scorestring.at(i)) {
		case '0':
			scoreboardsprites[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
			break;
		case '1':
			scoreboardsprites[i].setTextureRect(sf::IntRect(21, 0, 21, 32));
			break;
		case '2':
			scoreboardsprites[i].setTextureRect(sf::IntRect(42, 0, 21, 32));
			break;
		case '3':
			scoreboardsprites[i].setTextureRect(sf::IntRect(63, 0, 21, 32));
			break;
		case '4':
			scoreboardsprites[i].setTextureRect(sf::IntRect(84, 0, 21, 32));
			break;
		case '5':
			scoreboardsprites[i].setTextureRect(sf::IntRect(105, 0, 21, 32));
			break;
		case '6':
			scoreboardsprites[i].setTextureRect(sf::IntRect(126, 0, 21, 32));
			break;
		case '7':
			scoreboardsprites[i].setTextureRect(sf::IntRect(147, 0, 21, 32));
			break;
		case '8':
			scoreboardsprites[i].setTextureRect(sf::IntRect(168, 0, 21, 32));
			break;
		case '9':
			scoreboardsprites[i].setTextureRect(sf::IntRect(189, 0, 21, 32));
			break;
		}
	}
	for (int i = 0; i < 3; i++) {
		window.draw(scoreboardsprites[i]);
	}
	window.draw(smilesprite);      //draw menu buttons
	window.draw(debugsprite);
	window.draw(test1sprite);
	window.draw(test2sprite);
}
void Board::GameOver() {
	for (int i = 0; i < 400; i++) {					//reveal mines (no toggle)
		if (tiles[i].ismine == true) {
			tiles[i].minerevealed = true;
			tiles[i].isrevealed = true;
		}
	}
	smiletexture.loadFromFile("face_lose.png");
	smilesprite.setTexture(smiletexture);
}
void Board::ResetGame(RenderWindow &window, bool &playerstatus) {
	for (int i = 0; i < 400; i++) {             //reset values
		tiles[i].ismine = false;
		tiles[i].isrevealed = false;
		tiles[i].minerevealed = false;
		tiles[i].flagged = false;
		tiles[i].adjacentmines = 0;
	}
	int random;
	for (int i = 0; i < 50; i++) {               //new random mines
		random = rand() % 400;
		if (tiles[random].ismine != true) {
			tiles[random].ismine = true;
		}
		else {
			i--;
		}
	}

	for (int i = 0; i < 400; i++) {           // set up adjacent mines
		for (int u = 0; u < 8; u++)
		{
			if (tiles[i].neighbors[u] != nullptr) {
				if (tiles[i].neighbors[u]->ismine == true) {
					tiles[i].adjacentmines++;
				}
			}
		}
	}
	totalminecount = 50;
	scoreboard = totalminecount;
	smiletexture.loadFromFile("face_happy.png");  //reset smile face
	smilesprite.setTexture(smiletexture);
	playerstatus = true;
}
void Board::RevealMines(RenderWindow &window) {
		for (int i = 0; i < 400; i++) {
			if (tiles[i].ismine == true && tiles[i].minerevealed == false) {
				tiles[i].minerevealed = true;
			}
			else if (tiles[i].ismine == true && tiles[i].minerevealed == true) {
				tiles[i].minerevealed = false;
			}
		}
}
void Board::Victory() {
	for (int i = 0; i < 400; i++) {
		if (tiles[i].ismine == true) {
			tiles[i].flagged = true;
		}
	}
	smiletexture.loadFromFile("face_win.png");
	smilesprite.setTexture(smiletexture);
}
void Board::ClearBoard() {
	totalminecount = 0;
	scoreboard = totalminecount;
	for (int i = 0; i < 400; i++) {             //reset values
		tiles[i].ismine = false;
		tiles[i].isrevealed = false;
		tiles[i].minerevealed = false;
		tiles[i].flagged = false;
		tiles[i].adjacentmines = 0;
	}
}
void Board::LoadTest(int filenumber) {
	string filedata;
	ifstream file;
	int counter = 0;
	if (filenumber == 1) {
		file.open("testboard.brd");
	}
	else if (filenumber == 2) {
		file.open("testboard2.brd");
	}
	while (getline(file, filedata)) {
		for (unsigned int i = 0; i < filedata.length(); i++) {
			if (filedata.at(i) == '0') {
				tiles[counter].ismine = false;
			}
			else if (filedata.at(i) == '1') {
				tiles[counter].ismine = true;
				totalminecount++;
			}
			counter++;
		}
	}
	scoreboard = totalminecount;
	file.close();

	for (int i = 0; i < 400; i++) {           // set up new adjacent mines
		for (int u = 0; u < 8; u++)
		{
			if (tiles[i].neighbors[u] != nullptr) {
				if (tiles[i].neighbors[u]->ismine == true) {
					tiles[i].adjacentmines++;
				}
			}
		}
	}
}

Board::Board()
{
	smiletexture.loadFromFile("face_happy.png");   //load textures
	smilesprite.setTexture(smiletexture);
	smilesprite.setPosition(sf::Vector2f(384, 523));
	debugtexture.loadFromFile("debug.png");
	debugsprite.setTexture(debugtexture);
	debugsprite.setPosition(sf::Vector2f(560, 523));
	test1texture.loadFromFile("test_1.png");
	test1sprite.setTexture(test1texture);
	test1sprite.setPosition(sf::Vector2f(640, 523));
	test2texture.loadFromFile("test_2.png");
	test2sprite.setTexture(test2texture);
	test2sprite.setPosition(sf::Vector2f(720, 523));
	digitstexture.loadFromFile("digits.png");
	digitssprite.setTexture(digitstexture);
	minetexture.loadFromFile("mine.png");
	minesprite.setTexture(minetexture);
	flagtexture.loadFromFile("flag.png");
	flagsprite.setTexture(flagtexture);
	boardhiddentexture.loadFromFile("tile_hidden.png");
	boardhiddensprite.setTexture(boardhiddentexture);
	boardrevealedtexture.loadFromFile("tile_revealed.png");
	boardrevealedsprite.setTexture(boardrevealedtexture);
	one.loadFromFile("number_1.png");
	two.loadFromFile("number_2.png");
	three.loadFromFile("number_3.png");
	four.loadFromFile("number_4.png");
	five.loadFromFile("number_5.png");
	six.loadFromFile("number_6.png");
	seven.loadFromFile("number_7.png");
	eight.loadFromFile("number_8.png");
	scoreboardtexture.loadFromFile("digits.png");
	scoreboardsprites[0].setPosition(24, 523);
	scoreboardsprites[1].setPosition(45, 523);
	scoreboardsprites[2].setPosition(66, 523);
	for (int i = 0; i < 3; i++) {
		scoreboardsprites[i].setTexture(scoreboardtexture);
		scoreboardsprites[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
	}
	totalminecount = 50;
	scoreboard = totalminecount;

	int random;			//place mines
	srand(time(NULL));
	for (int i = 0; i < 50; i++) {
		random = rand() % 400;
		if (tiles[random].ismine != true) {
			tiles[random].ismine = true;
		}
		else {
			i--;
		}
	}

	tiles[0].neighbors[0] = nullptr;		//4 corner tile positions
	tiles[0].neighbors[1] = nullptr;
	tiles[0].neighbors[2] = nullptr;
	tiles[0].neighbors[3] = &tiles[0 + 1]; 
	tiles[0].neighbors[4] = &tiles[0 + 26];
	tiles[0].neighbors[5] = &tiles[0 + 25];
	tiles[0].neighbors[6] = nullptr;
	tiles[0].neighbors[7] = nullptr;
	tiles[0].cornertile = true;
	tiles[24].neighbors[7] = &tiles[24 - 1];
	tiles[24].neighbors[6] = &tiles[24 + 24];
	tiles[24].neighbors[5] = &tiles[24 + 25];
	tiles[24].neighbors[4] = nullptr;
	tiles[24].neighbors[3] = nullptr;
	tiles[24].neighbors[2] = nullptr;
	tiles[24].neighbors[1] = nullptr;
	tiles[24].neighbors[0] = nullptr;
	tiles[24].cornertile = true;
	tiles[375].neighbors[0] = nullptr;
	tiles[375].neighbors[1] = &tiles[375 - 25];
	tiles[375].neighbors[2] = &tiles[375 - 24];
	tiles[375].neighbors[3] = &tiles[375 + 1];
	tiles[375].neighbors[4] = nullptr;
	tiles[375].neighbors[5] = nullptr;
	tiles[375].neighbors[6] = nullptr;
	tiles[375].neighbors[7] = nullptr;
	tiles[375].cornertile = true;
	tiles[399].neighbors[0] = &tiles[399 - 26];
	tiles[399].neighbors[1] = &tiles[399 - 25];
	tiles[399].neighbors[2] = nullptr;
	tiles[399].neighbors[3] = nullptr;
	tiles[399].neighbors[4] = nullptr;
	tiles[399].neighbors[5] = nullptr;
	tiles[399].neighbors[6] = nullptr;
	tiles[399].neighbors[7] = &tiles[399 - 1];
	tiles[399].cornertile = true;

	for (int i = 1; i < 24; i++) {		//top edge position
		tiles[i].neighbors[7] = &tiles[i - 1];
		tiles[i].neighbors[6] = &tiles[i + 24];
		tiles[i].neighbors[5] = &tiles[i + 25];
		tiles[i].neighbors[4] = &tiles[i + 26];
		tiles[i].neighbors[3] = &tiles[i + 1];
		tiles[i].neighbors[2] = nullptr;
		tiles[i].neighbors[1] = nullptr;
		tiles[i].neighbors[0] = nullptr;
		tiles[i].edgetile = true;
	}
	for (int i = 376; i < 399; i++) {			//bottom edge position
		tiles[i].neighbors[7] = &tiles[i - 1];
		tiles[i].neighbors[0] = &tiles[i - 26];
		tiles[i].neighbors[1] = &tiles[i - 25];
		tiles[i].neighbors[2] = &tiles[i - 24];
		tiles[i].neighbors[3] = &tiles[i + 1]; 
		tiles[i].neighbors[4] = nullptr;
		tiles[i].neighbors[5] = nullptr;
		tiles[i].neighbors[6] = nullptr;
		tiles[i].edgetile = true;
	}
	for (int i = 25; i < 375; i += 25) {		//left edge
		tiles[i].neighbors[0] = nullptr; 
		tiles[i].neighbors[1] = &tiles[i - 25];
		tiles[i].neighbors[2] = &tiles[i - 24];
		tiles[i].neighbors[3] = &tiles[i + 1];
		tiles[i].neighbors[4] = &tiles[i + 26];
		tiles[i].neighbors[5] = &tiles[i + 25];
		tiles[i].neighbors[6] = nullptr;
		tiles[i].neighbors[7] = nullptr;
		tiles[i].edgetile = true;
	}
	for (int i = 49; i < 399; i += 25) {   //right edge
		tiles[i].neighbors[0] = &tiles[i - 26];
		tiles[i].neighbors[1] = &tiles[i - 25];
		tiles[i].neighbors[2] = nullptr;
		tiles[i].neighbors[3] = nullptr;
		tiles[i].neighbors[4] = nullptr;
		tiles[i].neighbors[5] = &tiles[i + 25];
		tiles[i].neighbors[6] = &tiles[i + 24];
		tiles[i].neighbors[7] = &tiles[i - 1];
		tiles[i].edgetile = true;
	}
	for (int i = 0; i < 400; i++) {

		if (tiles[i].cornertile != true && tiles[i].edgetile != true) {
			tiles[i].neighbors[7] = &tiles[i - 1]; //left
			tiles[i].neighbors[6] = &tiles[i + 24];  //downleft diagnol
			tiles[i].neighbors[5] = &tiles[i + 25];  //down
			tiles[i].neighbors[4] = &tiles[i + 26];  //downright diagnol
			tiles[i].neighbors[3] = &tiles[i + 1];   //right
			tiles[i].neighbors[2] = &tiles[i - 24];  //topright diagnol
			tiles[i].neighbors[1] = &tiles[i - 25];  //top
			tiles[i].neighbors[0] = &tiles[i - 26]; //topleft diagnol
		}
	}

	//setting up adjacent mines

	for (int i = 0; i < 400; i++) {
		for (int u = 0; u < 8; u++)
		{
			if (tiles[i].neighbors[u] != nullptr) {
				if (tiles[i].neighbors[u]->ismine == true) {
					tiles[i].adjacentmines++;
				}
			}
		}
	}
}


Board::~Board()
{
}
