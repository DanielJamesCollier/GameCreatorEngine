#pragma once
#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
#include "Logger.h"
#include "Sprite.h"


#include <exception>
#include <string>

class Mesh;
class GameObject;
class GLTexture;

class TestGame : public Game
{
public:
	TestGame(RenderingEngine* renderer);
	~TestGame();

	void init();
	void start();
	void stop();
	void run();
	void update();
	void render();
	
private:
	GameObject *root;
};
#endif