#include "Tile.h"


/*
Tile.cpp

file contains functions that are part of the Tile class. The tile class keeps coordinates of a tile, which are only used when the tile is part of a Pentomino which has yet to be locked into place. 
*/

//constructor in which Tile  coordinate are X,Y
Tile::Tile(int X, int Y)
{
	x = X;
	y = Y;
}

//default constructor, Tile coordinates are 0,0
Tile::Tile()
{
	x = 0;
	y = 0;
}

//used to determine coordinates of tile after rotating around the base pieces. (Rotation is CW/90 degrees ) 
void Tile::rotate(Tile base)
{
	int baseX = base.x;
	int baseY = base.y;
	int newX = 0;
	int newY = 0;
	int xDiff = x - baseX;
	int yDiff = y - baseY;
	if (xDiff == 0 && yDiff != 0)
	{
		newX = -yDiff;
		newY = xDiff;
	}
	else if (xDiff != 0 && yDiff == 0)
	{
		newX = yDiff;
		newY = xDiff;
	}
	/*else if (xDiff != 0 && yDiff > 0)
	{
		newX = yDiff;
		newY = xDiff;
	}*/
	else if (xDiff * yDiff < 0)
	{
		newX = xDiff;
		newY = -yDiff;
	}
	else if (xDiff * yDiff > 0)
	{
		newX = -xDiff;
		newY = yDiff;
	}
	x = baseX + newX;
	y = baseY + newY;
}


Tile::~Tile()
{
}
