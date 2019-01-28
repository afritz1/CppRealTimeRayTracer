#include <cstdlib>
#include <exception>
#include <iostream>

#include "SDL.h"

#include "Game/Game.h"

int main(int argc, char *argv[])
{
	try
	{
		Game g;
		g.loop();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		std::getchar();
	}

	return EXIT_SUCCESS;
}
