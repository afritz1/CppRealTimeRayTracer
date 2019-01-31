#ifndef RT_TILE_H
#define RT_TILE_H

class Tile
{
private:
	int x, y, width, height;
public:
	static constexpr int DEFAULT_SIZE = 32;

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;

	// Side length is truncated depending on how much room is available.
	void init(int x, int y, int length, int renderWidth, int renderHeight);
};

#endif
