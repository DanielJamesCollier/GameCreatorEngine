#include "TestGame.h"
#include "WindowEngine.h"
#include "RenderingEngine.h"
#include "GameObject.h"
#include "Mesh.h"
#include "MeshLoader.h"
#include "cout.h"
#include "ImageLoader.h"
#include "GLTexture.h"
#include "TextureCache.h"

#include <SDL.h>

TestGame::TestGame(RenderingEngine* renderer)
try : Game(renderer)
{
	init();
}
catch (const std::exception &e)
{
	std::string err = e.what();
	Logger::errorBlock("Exception caught", "Error: " + err, true);
}

TestGame::~TestGame()
{
	delete root;
}

void TestGame::init()
{
	root = new GameObject("root game object");
	root->setRenderingEngine(renderer);
	
	MeshLoader meshloader("Models/B-747.obj");
	//MeshLoader beach("Models/Beach.obj");
	//MeshLoader venice("Models/venice.obj");
	//MeshLoader minecraft("Models/Minecraft.obj");	
	
	//root->addChild(minecraft.getRoot());
	root->addChild(meshloader.getRoot());
	//root->addChild(venice.getRoot());

	

	// create and add floor to game
	Sprite* floor = new Sprite("Textures/rock.png", 100, 100);
	floor->setRotX(-90);

	floor->setPosZ(-50);
	floor->setPosX(-50);
	floor->setPosY(-9);
	root->addChild(floor);


	for (unsigned int i = 0; i < 300; ++i)
	{
		Sprite* sprite = new Sprite();

		sprite->setPosition(rand() % 30, rand() % 30, rand() % 30);
		root->addChild(sprite);
	}
	

	
}

void TestGame::start()
{
	if (!this->isRunning()) this->setRunning(true);
	else return;

	run();
}

void TestGame::stop()
{
	Logger::dumpLogsToFile();
}


void TestGame::run()
{
	int frame_count = 0;
	double current_time = SDL_GetTicks();
	double start_time = current_time;
	double passed_time = current_time;

	while (this->isRunning())
	{
		current_time = SDL_GetTicks();
		passed_time = current_time - start_time;

		frame_count++;

		update();
		render();

		//SDL_Delay(2);

		if (passed_time >= 1000)
		{
			std::cout << "FPS: " << frame_count << std::endl;
			start_time = current_time;
			frame_count = 0;
		}
	}
	stop();
}

float i = 0; 

void TestGame::update()
{
	input.update(this->isRunning());
	renderer->updateCamera();
	root->update(renderer->getWindow());
}

void TestGame::render()
{
	renderer->clearScreen();
	root->render();
	renderer->swapBackBuffer();
}