#include "WindowEngine.h"
#include "RenderingEngine.h"
#include "TestGame.h"
#include <SDL.h>

int main(int argc, char* argv[])
{
	WindowEngine    *window   = new WindowEngine("daniel", 30, 500, 1000, 700, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	RenderingEngine *renderer = new RenderingEngine(window);
	TestGame         game_one(renderer);
		
	game_one.start();

	return 0;
}