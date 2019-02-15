#ifndef RT_GAME_H
#define RT_GAME_H

#include "InputManager.h"
#include "../Cameras/Camera.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Renderer3D.h"
#include "../World/World.h"

class Surface;

class Game
{
private:
	Camera camera;
	InputManager inputManager;
	Renderer renderer;
	Renderer3D renderer3D;
	World world;
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
