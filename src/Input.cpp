#include "Input.h"

int Input::mouse_x = 0;
int Input::mouse_y = 0;

Input::Input()
{
}


Input::~Input()
{
}

int& Input::getX(void)
{
	return mouse_x;
}

int& Input::getY(void)
{
	return mouse_y;
}

bool Input::isKeyPressed(SDL_Scancode code)
{
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	if (state[code]) return true;

	return false;
}

void Input::update(bool &running)
{
	SDL_Event event;

	SDL_GetMouseState(&mouse_x, &mouse_y);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				running = false;
				break;
			}
		}
	}
}