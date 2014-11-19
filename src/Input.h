#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input
{
public:
	Input();
	~Input();

	static int& getX(void);
	static int& getY(void);

	static bool isKeyPressed(SDL_Scancode code);

	void update(bool &running);

private:

	static int mouse_x;
	static int mouse_y;

};
#endif INPUT

