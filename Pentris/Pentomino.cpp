#include "Pentomino.h"
#include <iostream>

/*
Pentomino.cpp

file contains functions that are part of the Pentomino class. The Pentomino class holds five tiles, which are arranged in one of 18 patterns.
*/

	//Constructor, creates a pentomino with the given shape based at the specified coordinates.
	Pentomino::Pentomino(PentType type, int baseX, int baseY)
	{
		p0 = Tile(baseX, baseY);
		switch (type)
		{
		case F1:
			p1 = Tile(baseX - 1, baseY);
			p2 = Tile(baseX, baseY - 1);
			p3 = Tile(baseX, baseY + 1);
			p4 = Tile(baseX + 1, baseY - 1);
			break;
		case F2:
			p1 = Tile(baseX + 1, baseY);
			p2 = Tile(baseX, baseY - 1);
			p3 = Tile(baseX, baseY + 1);
			p4 = Tile(baseX - 1, baseY - 1);
			break;
		case L1:
			p1 = Tile(baseX, baseY-1);
			p2 = Tile(baseX, baseY-2);
			p3 = Tile(baseX, baseY+1);
			p4 = Tile(baseX+1, baseY+1);
			break;
		case L2:
			p1 = Tile(baseX, baseY - 1);
			p2 = Tile(baseX, baseY - 2);
			p3 = Tile(baseX, baseY + 1);
			p4 = Tile(baseX - 1, baseY + 1);
			break;
		case P1:
			p1 = Tile(baseX, baseY + 1);
			p2 = Tile(baseX, baseY - 1);
			p3 = Tile(baseX + 1, baseY -1);
			p4 = Tile(baseX + 1, baseY);
			break;
		case P2:
			p1 = Tile(baseX, baseY + 1);
			p2 = Tile(baseX, baseY - 1);
			p3 = Tile(baseX - 1, baseY - 1);
			p4 = Tile(baseX - 1, baseY);
			break;
		case N1:
			p1 = Tile(baseX, baseY -1);
			p2 = Tile(baseX -1, baseY -1);
			p3 = Tile(baseX + 1, baseY);
			p4 = Tile(baseX + 2, baseY);
			break;
		case N2:
			p1 = Tile(baseX, baseY - 1);
			p2 = Tile(baseX + 1, baseY - 1);
			p3 = Tile(baseX - 1, baseY);
			p4 = Tile(baseX - 2, baseY);
			break;
		case Y1:
			p1 = Tile(baseX, baseY -1);
			p2 = Tile(baseX + 1, baseY);
			p3 = Tile(baseX -1, baseY);
			p4 = Tile(baseX -2, baseY);
			break;
		case Y2:
			p1 = Tile(baseX, baseY - 1);
			p2 = Tile(baseX - 1, baseY);
			p3 = Tile(baseX + 1, baseY);
			p4 = Tile(baseX + 2, baseY);
			break;
		case T:
			p1 = Tile(baseX + 1, baseY);
			p2 = Tile(baseX + 1, baseY -1);
			p3 = Tile(baseX + 1, baseY + 1);
			p4 = Tile(baseX - 1, baseY);
			break;
		case U:
			p1 = Tile(baseX + 1, baseY);
			p2 = Tile(baseX + 1, baseY -1);
			p3 = Tile(baseX - 1, baseY);
			p4 = Tile(baseX - 1, baseY -1);

		case V:
			p1 = Tile(baseX + 1, baseY);
			p2 = Tile(baseX + 2, baseY);
			p3 = Tile(baseX, baseY - 1);
			p4 = Tile(baseX, baseY - 2);
			break;
		case W:
			p1 = Tile(baseX - 1, baseY);
			p2 = Tile(baseX - 1, baseY-1);
			p3 = Tile(baseX, baseY + 1);
			p4 = Tile(baseX + 1, baseY + 1);
			break;
		case X:
			p1 = Tile(baseX + 1, baseY);
			p2 = Tile(baseX - 1, baseY);
			p3 = Tile(baseX, baseY + 1);
			p4 = Tile(baseX, baseY - 1);
			break;
		case Z1:
			p1 = Tile(baseX + 1, baseY);
			p2 = Tile(baseX + 1, baseY - 1);
			p3 = Tile(baseX - 1, baseY);
			p4 = Tile(baseX - 1, baseY + 1);
			break;
		case Z2:
			p1 = Tile(baseX - 1, baseY);
			p2 = Tile(baseX - 1, baseY - 1);
			p3 = Tile(baseX + 1, baseY);
			p4 = Tile(baseX + 1, baseY + 1);
			break;
		default:
			p1 = Tile(baseX + 1, baseY);
			p2 = Tile(baseX + 2, baseY);
			p3 = Tile(baseX - 1, baseY);
			p4 = Tile(baseX - 2, baseY);
			break;
		}
		updatePieces();
	}

	//creates a new Pentomino whose tiles correspond to the calling penominos, should it make the move specified by the argument.
	//the pentomino created by attemptMove is intended detect whether a move is legal or not before moving the intended Pentomino itself.
	Pentomino Pentomino::attemptMove(PentominoMoves moveType)
	{
		Pentomino attempt = *this;
		attempt.makeMove(moveType);
		return attempt;
	}

	//moves Pentomino tiles based on argument given. Should only be called after checking for legality of move using AttemptMove.
	void Pentomino::makeMove(PentominoMoves moveType)
	{
		switch (moveType)
		{
		case(LEFT):
			p0.x -= 1;
			p1.x -= 1;
			p2.x -= 1;
			p3.x -= 1;
			p4.x -= 1;
			break;
		case(RIGHT):
			p0.x += 1;
			p1.x += 1;
			p2.x += 1;
			p3.x += 1;
			p4.x += 1;
			break;
		case(DOWN):
			p0.y += 1;
			p1.y += 1;
			p2.y += 1;
			p3.y += 1;
			p4.y += 1;
			break;
		case(ROTATE):
			p1.rotate(p0);
			p2.rotate(p0);
			p3.rotate(p0);
			p4.rotate(p0);
			break;
		}
		updatePieces();
	}

	//to be called any time tiles are modified
	void Pentomino::updatePieces()
	{
		pieces[0] = p0;
		pieces[1] = p1;
		pieces[2] = p2;
		pieces[3] = p3;
		pieces[4] = p4;
	}

	Pentomino::~Pentomino()
	{
	}