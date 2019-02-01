#ifndef RT_GAME_H
#define RT_GAME_H

#include "InputManager.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Renderer3D.h"

class Surface;

class Game
{
private:
	InputManager inputManager;
	Renderer renderer;
	Renderer3D renderer3D;
	double resolutionScale;

	void handleInput(bool &running);
	void resizeWindow(int width, int height);
	void saveScreenshot(const Surface &surface);
	void tick(double dt);
	void render(double dt);
public:
	Game();

	void loop();
};

#endif
