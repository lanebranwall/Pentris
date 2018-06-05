#include "game.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

/*
Game.cpp

file contains variables and functions that control the gameplay of Pentris.
Game.cpp holds the gameboard, related variables, as well as functions which relate to player control
*/


//"constant" variables
static const int boardHeight = 25;
static const int boardWidth = 13;
static const int boardX = 225;
static const int boardY = 50;
static const int nextX = 390;
static const int nextY = 250;
static const int startX = 6;
static const int startY = 2;
SDL_Texture* BG = createTexture("images/Background.png");
SDL_Texture* tTex = createTexture("images/SimpleTile.png");
SDL_Texture* pause = createTexture("images/pause.png");

//game vairables
static Tile* gameBoard[boardHeight][boardWidth];
static int ticksSinceDrop = 0;
static int ticksToDrop = 60;
static int dropsOnPiece = 0;
static Pentomino* currentPiece = new Pentomino(randomType(), startX, startY);
static Pentomino* nextPiece = new Pentomino(randomType(), startX, startY);
static int score = 0;
static int level = 0;
static int lines = 0;
static bool paused = false;
static bool gameOver = false;

//other variables
static bool seeded = false;

//adds all tiles on the gameboard to the renderstate, including currentPiece.
void renderBoard() 
{
	renderTexture(BG, 0, 0);
	renderNumber(score, 9, 25, 80);
	renderNumber(lines, 4, 110, 154);
	renderNumber(level, 1, 161, 118);
	for (int i = 0; i < boardHeight; i++)//render all tiles currently on the board
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (gameBoard[i][j] != nullptr)
			{
				renderTexture(tTex, boardX + 15 * j, boardY + 15 * i);
			}
		}
	}
	if (currentPiece != nullptr)//render all tiles in currentPiece
	{
		for (Tile t : currentPiece->pieces)
		{
			renderTexture(tTex, boardX + 15 * t.x, boardY + 15 * t.y);
		}
	}
	if (nextPiece != nullptr)//render all tiles in nextPiece
	{
		for (Tile t : nextPiece->pieces)
		{
			renderTexture(tTex, nextX + 15 * t.x, nextY + 15 * t.y);
		}
	}
	if (paused) renderTexture(pause, 258 , 219); //render pause message if game is paused
}


//Called once per game tick. Performs any logical checks and/or actions that do not rely on user actions.
void gameStateUpdate()
{
	if (paused) return;
	if (++ticksSinceDrop >= ticksToDrop) //Increments ticksSinceDrop
	{
		Pentomino attempt = currentPiece->attemptMove(DOWN);
		if (isLegalMove(attempt))
		{
			currentPiece->makeMove(DOWN);
			ticksSinceDrop = 0;
		}
		else newPiece();
	}
	if (level < 5 && lines/15 > level)
	{
		level = lines / 15;
		if (level > 5) level = 5;
		ticksToDrop = 60 - level * 10;
	}
}

//takes in an SDL_Keycode, and runs any interaction associated with the key. 
void readKeyInput(SDL_Keycode key)
{
	if (paused)
	{
		if (key == SDLK_p)
		{
			paused = false;
			return;
		}
	}
	switch (key)
	{
	case SDLK_SPACE:
		{
			Pentomino attempt = currentPiece->attemptMove(ROTATE);
			if (isLegalMove(attempt)) currentPiece->makeMove(ROTATE);
			break;
		}
	case SDLK_LEFT:
		{
			Pentomino attempt = currentPiece->attemptMove(LEFT);
			if (isLegalMove(attempt)) currentPiece->makeMove(LEFT);
			break;
		}
	case SDLK_RIGHT:
		{
			Pentomino attempt = currentPiece->attemptMove(RIGHT);
			if (isLegalMove(attempt)) currentPiece->makeMove(RIGHT);
			break;
		}
	case SDLK_DOWN:
		{
			Pentomino attempt = currentPiece->attemptMove(DOWN);
			if (isLegalMove(attempt))
			{
				currentPiece->makeMove(DOWN);
				ticksSinceDrop = 0;
				dropsOnPiece++;
			}
			else newPiece();
			break;
		}
	case SDLK_p:
		{
			paused = true;
			break;
		}
	}
}

//takes in a Pentomino as an arguments.
//Returns false if any tile on the Pentomino collides with any locked tiles on the board, or is out of bounds, otherwise returns true.
bool isLegalMove(Pentomino attempt)
{
	for (Tile t : attempt.pieces)
	{
		if (t.x < 0 || t.x >= boardWidth)
		{
			return false;
		}
		if (t.y < 0 || t.y >= boardHeight)
		{
			return false;
		}
		if (gameBoard[t.y][t.x] != nullptr)
		{
			return false;
		}
	}
	return true;
}

//To be called when the controlled Pentomino (currentPiece) is locked into position.
//Adds all of CurrentPiece's tiles to the gameboard in the correct location, sets nextPiece to CurrentPiece, and creates a new piece for nextPiece. 
void newPiece()
{
	int drops = dropsOnPiece;
	dropsOnPiece = 0;
	std::set<int> rows = checkRows(*currentPiece);
	for (Tile t : currentPiece->pieces)
	{
		gameBoard[t.y][t.x] = &Tile();
	}
	delete currentPiece; //remove currentPiece from memory, as it is no longer being used/referenced.
	currentPiece = nextPiece;
	nextPiece = new Pentomino(randomType(), startX, startY);
	int rowsCleared = checkAndClear(rows);
	addScore(drops, rowsCleared);
	lines += rowsCleared;
	if (lines > 9999) lines = lines % 10000;
	if (!isLegalMove(*currentPiece))
	{
		gameOver = true;
	}
}

//returns a list of all rows that the Pentomino inPlace sits on.
std::set<int> checkRows(Pentomino inPlace)
{
	std::set<int> heightList;
	for (Tile t : inPlace.pieces)
	{
		heightList.insert(t.y);
	}
	return heightList;
}

//Takes in a set of rows. Checks each row in the set to see if it is full, if it is, it clears the row, bringing every row above it down by one.
//returns the number of rows cleared.
int checkAndClear(std::set<int> rows)
{
	int rowsCleared = 0;
	for (int r : rows)
	{
		if (rowFull(r))
		{
			for (int i = r; i > 0; i--)
			{
				for(int j = 0; j < boardWidth; j++)
				gameBoard[i][j] = gameBoard[i - 1][j];
			}
			for (Tile* t : gameBoard[0])
			{
				t = nullptr;
			}
			rowsCleared++;
		}
	}
	return rowsCleared;
}

//checks if the row specified by the argument is full of tiles or not. Returns true if the specified row is on the board and the row is fully occupied, otherwise false.
bool rowFull(int rowNum)
{
	if (rowNum < 0 || rowNum >= boardHeight) return false;
	for (int i = 0; i < boardWidth; i++)
	{
		if (gameBoard[rowNum][i] == nullptr) return false;
	}
	return true;
}

//called when a Pentomino is locked into place. adds to the current score based on level, number of manual drops on the Pentomino, and number of rows cleared.
void addScore(int drops, int rows)
{
	int multiplier = level + 1;
	int toAdd = 0;
	toAdd += 5 * multiplier;
	toAdd += drops * multiplier;
	switch (rows)
	{
	case 1:
		score += 50 * multiplier;
		break;
	case 2:
		score += 125 * multiplier;
		break;
	case 3:
		score += 750 * multiplier;
		break;
	case 4:
		score += 2000 * multiplier;
		break;
	case 5:
		score += 5000 * multiplier;
		break;
	}
	score += toAdd;
	if (score >= 999999999) score = 999999999;
}

//returns true if Game Over state is in effect.
bool isGameOver()
{
	return gameOver;
}

//returns a random PentType, with equal probability
PentType randomType()
{
	if (!seeded)
	{
		srand(time(NULL));
		seeded = true;
	}
	int type = rand() % numberOfPentominoTypes;
	switch (type)
	{
	case 1:
		return F1;
		break;
	case 2:
		return F2;
		break;
	case 3:
		return L1;
		break;
	case 4:
		return L2;
		break;
	case 5:
		return P1;
		break;
	case 6:
		return P2;
		break;
	case 7:
		return N1;
		break;
	case 8:
		return N2;
		break;
	case 9:
		return Y1;
		break;
	case 10:
		return Y2;
		break;
	case 11:
		return T;
		break;
	case 12:
		return U;
		break;
	case 13:
		return V;
		break;
	case 14:
		return W;
		break;
	case 15:
		return X;
		break;
	case 16:
		return Z1;
		break;
	case 17:
		return Z2;
		break;
	}
	return I;
}

//Removes currentPiece and nextPiece from memory. To be called at end of game.
void clearGame()
{
	delete currentPiece;
	delete nextPiece;
}