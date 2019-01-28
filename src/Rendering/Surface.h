#ifndef RT_SURFACE_H
#define RT_SURFACE_H

#include <cstdint>
#include <string>

struct SDL_Surface;

class Surface
{
private:
	SDL_Surface *surface;
public:
	Surface();
	Surface(SDL_Surface *surface);
	Surface(const Surface&) = delete;
	Surface(Surface &&surface);
	~Surface();

	Surface &operator=(const Surface&) = delete;
	Surface &operator=(Surface &&surface);

	// Wrapper function for SDL_LoadBMP(). Also converts to the given pixel format.
	static Surface loadBMP(const std::string &filename, uint32_t format);

	// Wrapper function for SDL_CreateRGBSurfaceWithFormat() in SDL 2.0.5.
	static Surface createWithFormat(int width, int height, int depth, uint32_t format);

	// Wrapper function for SDL_CreateRGBSurfaceWithFormatFrom() in SDL 2.0.5.
	static Surface createWithFormatFrom(void *pixels, int width, int height,
		int depth, int pitch, uint32_t format);

	int getWidth() const;
	int getHeight() const;
	void *getPixels() const;
	SDL_Surface *get() const;
};

#endif
