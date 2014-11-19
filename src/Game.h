#pragma once
#ifndef GAME_H
#define GAME_H

#include "Input.h"

class WindowEngine;
class RenderingEngine;

class Game
{
public:
	Game(RenderingEngine* renderer)
	{
		this->renderer = renderer;
		this->running = false;
	}

	virtual ~Game()
	{
		delete renderer;
	}

	virtual void init()   = 0;
	virtual void start()  = 0;
	virtual void stop()   = 0;
	virtual void run()	  = 0;
	virtual void update() = 0;
	virtual void render() = 0;

private:
	bool running;

protected:
	RenderingEngine* renderer;
	Input input;

	inline bool& isRunning() { return running; };
	inline void setRunning(bool running) { this->running = running; }
	
};
#endif

