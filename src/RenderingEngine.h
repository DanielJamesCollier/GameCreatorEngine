#pragma once
#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <glew.h>

class Mesh;
class Sprite;
class Camera;
class ShaderCache;
class TextureCache;
class ShaderProgram;
class ShaderProgramCache;
class WindowEngine;

class RenderingEngine
{
public:
	RenderingEngine(WindowEngine* window);
	~RenderingEngine();

	void setCamera(Camera* cam);
	ShaderProgram* getBoundProgram();
	GLuint getBoundProgramId();

	void updateCamera();

	void render(Sprite* sprite);
	void render(Sprite* sprite, ShaderProgram* program);
	void render(Mesh* mesh);
	void render(Mesh* mesh, ShaderProgram* program);

	void clearScreen();
	void swapBackBuffer();

	inline WindowEngine* getWindow() { return window; }

private:
	Camera* main_camera;
	WindowEngine* window;

	ShaderProgramCache* program_cache;
	ShaderCache* shaders;
	TextureCache* textures;

	ShaderProgram* bound_program;
};
#endif

