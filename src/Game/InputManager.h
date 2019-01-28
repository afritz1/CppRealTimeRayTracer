#ifndef RT_INPUT_MANAGER_H
#define RT_INPUT_MANAGER_H

#include <cstdint>

#include "SDL.h"

#include "../Math/Int2.h"

class InputManager
{
private:
	Int2 mouseDelta;
public:
	InputManager();

	bool keyPressed(const SDL_Event &e, SDL_Keycode keycode) const;
	bool keyReleased(const SDL_Event &e, SDL_Keycode keycode) const;
	bool keyIsDown(SDL_Scancode scancode) const;
	bool keyIsUp(SDL_Scancode scancode) const;
	bool mouseButtonPressed(const SDL_Event &e, uint8_t button) const;
	bool mouseButtonReleased(const SDL_Event &e, uint8_t button) const;
	bool mouseButtonIsDown(uint8_t button) const;
	bool mouseButtonIsUp(uint8_t button) const;
	bool mouseWheeledUp(const SDL_Event &e) const;
	bool mouseWheeledDown(const SDL_Event &e) const;
	bool windowResized(const SDL_Event &e) const;
	bool applicationExit(const SDL_Event &e) const;
	Int2 getMousePosition() const;
	Int2 getMouseDelta() const;

	// Sets whether the mouse should move during motion events.
	void setRelativeMouseMode(bool active);

	// Updates input values whose associated SDL functions should only be called once 
	// per frame.
	void update();
};

#endif
