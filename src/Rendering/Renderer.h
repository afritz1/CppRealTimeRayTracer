#ifndef RT_RENDERER_H
#define RT_RENDERER_H

#include <cstdint>
#include <string>

#include "../Math/Int2.h"

class Camera;
class Renderer3D;
class Surface;
class World;

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Window;

class Renderer
{
private:
	static const char *DEFAULT_RENDER_SCALE_QUALITY;
	static const std::string DEFAULT_TITLE;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *nativeTexture, *gameWorldTexture; // Frame buffers.

	// Helper method for making a renderer context.
	static SDL_Renderer *createRenderer(SDL_Window *window);
public:
	// Only defined so members are initialized for Game ctor exception handling.
	Renderer();
	~Renderer();

	// Default bits per pixel.
	static const int DEFAULT_BPP;

	// The default pixel format for all software surfaces, ARGB8888.
	static const uint32_t DEFAULT_PIXELFORMAT;

	// Gets the width and height of the active window.
	Int2 getWindowDimensions() const;

	// Gets a screenshot of the renderer's current frame.
	Surface getScreenshot() const;

	// Wrapper methods for SDL_CreateTexture.
	SDL_Texture *createTexture(uint32_t format, int access, int w, int h);
	SDL_Texture *createTextureFromSurface(SDL_Surface *surface);

	void init(int width, int height, bool fullscreen);
	void init3D(double resolutionScale, Renderer3D &renderer3D);

	void resize(int width, int height, double resolutionScale, Renderer3D &renderer3D);

	// Sets whether the program is windowed or fullscreen.
	void setFullscreen(bool fullscreen);

	// Sets the window icon to be the given surface.
	void setWindowIcon(SDL_Surface *icon);

	// Sets the window title.
	void setWindowTitle(const std::string &title);

	// Teleports the mouse to a location in the window.
	void warpMouse(int x, int y);

	// Clears the native frame buffer.
	void clear();

	// Draws texture to the frame buffer.
	void draw(SDL_Texture *texture, int x, int y, int w, int h);

	// Renders the game world to the internal frame buffer.
	void render(const Camera &camera, const World &world, Renderer3D &renderer3D);

	// Refreshes the displayed frame buffer.
	void present();
};

#endif
