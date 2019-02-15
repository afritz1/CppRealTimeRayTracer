#include "SDL.h"

#include "Game.h"
#include "../Rendering/Surface.h"

Game::Game()
{
	// Initialize camera.
	const Double3 eye(0.0, 1.0, 0.0);
	const Double3 direction(1.0, 0.0, 0.0);
	this->camera = Camera(eye, direction);

	// Initialize renderer.
	const int width = 1280;
	const int height = 720;
	const bool fullscreen = false;
	this->resolutionScale = 0.50;
	this->renderer.init(width, height, fullscreen);
	this->renderer.init3D(this->resolutionScale, this->renderer3D);

	// Initialize world.
	const Double3 fogColor(0.2, 0.5, 1.0);
	const double fogDistance = 20.0;
	this->world.init(fogColor, fogDistance);

	Rect rect;
	rect.init(
		Double3(5.0, 0.0, 0.0),
		Double3::UnitY,
		Double3::UnitZ,
		2.0,
		1.0,
		Double2::Zero,
		Double2(1.0, 1.0),
		0);

	this->world.addRect(std::move(rect));
}

void Game::handleInput(bool &running)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		const bool applicationExit = this->inputManager.applicationExit(e);
		const bool windowResized = this->inputManager.windowResized(e);
		const bool takeScreenshot = this->inputManager.keyPressed(e, SDLK_PRINTSCREEN);

		if (applicationExit)
		{
			running = false;
		}

		if (windowResized)
		{
			const int width = e.window.data1;
			const int height = e.window.data2;
			this->resizeWindow(width, height);
		}

		if (takeScreenshot)
		{
			// Save a screenshot to the local folder.
			const Surface screenshot = this->renderer.getScreenshot();
			this->saveScreenshot(screenshot);
		}
	}
}

void Game::resizeWindow(int width, int height)
{
	this->renderer.resize(width, height, this->resolutionScale, this->renderer3D);
}

void Game::saveScreenshot(const Surface &surface)
{
	printf("Not implemented.\n");
}

void Game::tick(double dt)
{
	const double dxRadians = 0.25;
	const double dyRadians = 0.0;
	const double pitchLimit = 85.0;
	this->camera.rotate(dxRadians, dyRadians, pitchLimit);
}

void Game::render(double dt)
{
	this->renderer.clear();
	this->renderer.render(this->camera, this->world, this->renderer3D);
	this->renderer.present();
}

void Game::loop()
{
	bool running = true;

	while (running)
	{
		SDL_Delay(16);

		this->inputManager.update();

		this->handleInput(running);

		const double dt = 1.0 / 60.0;
		this->tick(dt);

		this->render(dt);
	}
}
