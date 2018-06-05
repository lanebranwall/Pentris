#pragma once

#include "tile.h"
#include "Pentomino.h"
#include "PentTypes.h"
#include "Render.h"
#include <set>



void renderBoard();
void gameStateUpdate();
void readKeyInput(SDL_Keycode key);
bool isLegalMove(Pentomino attempt);
void newPiece();
std::set<int> checkRows(Pentomino inPlace);
int checkAndClear(std::set<int> rows);
bool rowFull(int rowNum);
void addScore(int time, int rows);
bool isGameOver();
PentType randomType();
void clearGame();
