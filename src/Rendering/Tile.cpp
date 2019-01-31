#include <algorithm>
#include <cassert>

#include "Tile.h"

int Tile::getX() const
{
	return this->x;
}

int Tile::getY() const
{
	return this->y;
}

int Tile::getWidth() const
{
	return this->width;
}

int Tile::getHeight() const
{
	return this->height;
}

void Tile::init(int x, int y, int length, int renderWidth, int renderHeight)
{
	// Starting position must be in frame buffer.
	assert(x >= 0);
	assert(x < renderWidth);
	assert(y >= 0);
	assert(y < renderHeight);
	assert(length > 0);

	this->x = x;
	this->y = y;
	this->width = std::min(length, renderWidth - x);
	this->height = std::min(length, renderHeight - y);
}
