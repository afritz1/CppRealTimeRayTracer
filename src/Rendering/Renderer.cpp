#include <cassert>

#include "SDL.h"

#include "Renderer.h"
#include "Surface.h"

const char *Renderer::DEFAULT_RENDER_SCALE_QUALITY = "nearest";
const std::string Renderer::DEFAULT_TITLE = "C++ Ray Tracer";
const int Renderer::DEFAULT_BPP = 32;
const uint32_t Renderer::DEFAULT_PIXELFORMAT = SDL_PIXELFORMAT_ARGB8888;

Renderer::Renderer()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->nativeTexture = nullptr;
	this->gameWorldTexture = nullptr;
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(this->window);

	// This also destroys the frame buffer textures.
	SDL_DestroyRenderer(this->renderer);
}

SDL_Renderer *Renderer::createRenderer(SDL_Window *window)
{
	// Automatically choose the best driver.
	const int bestDriver = -1;

	SDL_Renderer *renderer = SDL_CreateRenderer(window, bestDriver, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		return nullptr;
	}

	// Set pixel interpolation hint.
	SDL_bool status = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,
		Renderer::DEFAULT_RENDER_SCALE_QUALITY);
	if (status != SDL_TRUE)
	{
		printf("Could not set interpolation hint.\n");
	}

	// Set the size of the render texture to be the size of the whole screen
	// (it automatically scales otherwise).
	SDL_Surface *nativeSurface = SDL_GetWindowSurface(window);

	// If this fails, we might not support hardware accelerated renderers for some reason
	// (such as with Linux), so we retry with software.
	if (!nativeSurface)
	{
		printf("Failed to init accelerated SDL_Renderer, trying software fallback.\n");

		SDL_DestroyRenderer(renderer);

		renderer = SDL_CreateRenderer(window, bestDriver, SDL_RENDERER_SOFTWARE);
		if (renderer == nullptr)
		{
			printf("Failed to init software SDL_Renderer.\n");
			return nullptr;
		}

		nativeSurface = SDL_GetWindowSurface(window);
	}

	if (nativeSurface == nullptr)
	{
		return nullptr;
	}

	// Set the device-independent resolution for rendering (i.e., the 
	// "behind-the-scenes" resolution).
	SDL_RenderSetLogicalSize(renderer, nativeSurface->w, nativeSurface->h);

	return renderer;
}

Int2 Renderer::getWindowDimensions() const
{
	Int2 dims;
	SDL_GetWindowSize(this->window, &dims.x, &dims.y);
	return dims;
}

Surface Renderer::getScreenshot() const
{
	const Int2 dimensions = this->getWindowDimensions();
	Surface screenshot = Surface::createWithFormat(dimensions.x, dimensions.y,
		Renderer::DEFAULT_BPP, Renderer::DEFAULT_PIXELFORMAT);

	const int status = SDL_RenderReadPixels(this->renderer, nullptr,
		screenshot.get()->format->format, screenshot.get()->pixels, screenshot.get()->pitch);

	if (status != 0)
	{
		printf("Couldn't take screenshot, %s.\n", SDL_GetError());
	}

	return screenshot;
}

SDL_Texture *Renderer::createTexture(uint32_t format, int access, int w, int h)
{
	return SDL_CreateTexture(this->renderer, format, access, w, h);
}

SDL_Texture *Renderer::createTextureFromSurface(SDL_Surface *surface)
{
	return SDL_CreateTextureFromSurface(this->renderer, surface);
}

void Renderer::init(int width, int height, bool fullscreen)
{
	assert(width > 0);
	assert(height > 0);

	// Initialize window. The SDL surface is obtained from this window.
	this->window = [width, height, fullscreen]()
	{
		const std::string &title = Renderer::DEFAULT_TITLE;
		const int position = fullscreen ? SDL_WINDOWPOS_UNDEFINED : SDL_WINDOWPOS_CENTERED;
		const uint32_t flags = SDL_WINDOW_RESIZABLE |
			(fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

		// If fullscreen is true, then width and height are ignored. They are stored
		// behind the scenes for when the user changes to windowed mode, however.
		return SDL_CreateWindow(title.c_str(), position, position, width, height, flags);
	}();

	if (this->window == nullptr)
	{
		printf("Error: SDL_CreateWindow.\n");
		return;
	}

	// Initialize renderer context.
	this->renderer = Renderer::createRenderer(this->window);

	// Use window dimensions, just in case it's fullscreen and the given width and
	// height are ignored.
	Int2 windowDimensions = this->getWindowDimensions();

	// Initialize native frame buffer.
	this->nativeTexture = this->createTexture(Renderer::DEFAULT_PIXELFORMAT,
		SDL_TEXTUREACCESS_TARGET, windowDimensions.x, windowDimensions.y);

	if (this->nativeTexture == nullptr)
	{
		printf("Error: couldn't create native frame buffer, %s.\n", SDL_GetError());
		return;
	}

	// Don't initialize the game world buffer until the 3D renderer is initialized.
	this->gameWorldTexture = nullptr;
}

void Renderer::resize(int width, int height, double resolutionScale)
{
	// The window's dimensions are resized automatically. The renderer's are not.
	const auto *nativeSurface = SDL_GetWindowSurface(this->window);
	assert(nativeSurface->w == width);
	assert(nativeSurface->h == height);

	SDL_RenderSetLogicalSize(this->renderer, width, height);

	// Reinitialize native frame buffer.
	SDL_DestroyTexture(this->nativeTexture);
	this->nativeTexture = this->createTexture(Renderer::DEFAULT_PIXELFORMAT,
		SDL_TEXTUREACCESS_TARGET, width, height);

	if (this->nativeTexture == nullptr)
	{
		printf("Error: couldn't recreate native frame buffer, %s.\n", SDL_GetError());
		return;
	}

	// Rebuild the 3D renderer if initialized.
	/*if (this->softwareRenderer.isInited())
	{
		// Height of the game world view in pixels. Determined by whether the game 
		// interface is visible or not.
		const int viewHeight = this->getViewHeight();

		// Make sure render dimensions are at least 1x1.
		const int renderWidth = std::max(static_cast<int>(width * resolutionScale), 1);
		const int renderHeight = std::max(static_cast<int>(viewHeight * resolutionScale), 1);

		// Reinitialize the game world frame buffer.
		SDL_DestroyTexture(this->gameWorldTexture);
		this->gameWorldTexture = this->createTexture(Renderer::DEFAULT_PIXELFORMAT,
			SDL_TEXTUREACCESS_STREAMING, renderWidth, renderHeight);
		DebugAssert(this->gameWorldTexture != nullptr,
			"Couldn't recreate game world texture, " + std::string(SDL_GetError()));

		// Resize 3D renderer.
		this->softwareRenderer.resize(renderWidth, renderHeight);
	}*/
}

void Renderer::setFullscreen(bool fullscreen)
{
	// Use "fake" fullscreen for now.
	uint32_t flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
	SDL_SetWindowFullscreen(this->window, flags);

	// Reset the cursor to the center of the screen for consistency.
	const Int2 windowDims = this->getWindowDimensions();
	this->warpMouse(windowDims.x / 2, windowDims.y / 2);
}

void Renderer::setWindowIcon(SDL_Surface *icon)
{
	SDL_SetWindowIcon(this->window, icon);
}

void Renderer::setWindowTitle(const std::string &title)
{
	SDL_SetWindowTitle(this->window, title.c_str());
}

void Renderer::warpMouse(int x, int y)
{
	SDL_WarpMouseInWindow(this->window, x, y);
}

void Renderer::clear()
{
	SDL_SetRenderTarget(this->renderer, this->nativeTexture);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);
}

void Renderer::present()
{
	SDL_SetRenderTarget(this->renderer, nullptr);
	SDL_RenderCopy(this->renderer, this->nativeTexture, nullptr, nullptr);
	SDL_RenderPresent(this->renderer);
}
