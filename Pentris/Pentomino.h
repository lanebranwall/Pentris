#pragma once

#include "PentTypes.h"
#include "Tile.h"

enum PentominoMoves { LEFT, RIGHT, DOWN, ROTATE };

class Pentomino
{
	

public:
	Pentomino(PentType type, int baseX, int baseY);
	Tile pieces[5] = { p0,p1,p2,p3,p4 };
	void rotate();
	Pentomino attemptMove(PentominoMoves moveType);
	void makeMove(PentominoMoves moveType);
	~Pentomino();
private:
	void updatePieces();
	Tile p0;
	Tile p1;
	Tile p2;
	Tile p3;
	Tile p4;
};



