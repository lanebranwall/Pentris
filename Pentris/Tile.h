#pragma once
class Tile
{



public:
	int x;
	int y;

	Tile(int x, int y);
	Tile();
	void rotate(Tile center);
	~Tile();
};

