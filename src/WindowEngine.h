#pragma once
#ifndef WINDOWENGINE_H
#define WINDOWENGINE_H

#include <SDL.h>
#include <string>
#include <glew.h>

class WindowEngine
{
public:

	WindowEngine();
	WindowEngine(std::string title, GLuint x, GLuint y, GLuint w, GLuint h, GLuint flags);
	~WindowEngine();

	float& getWidth();
	float& getHeight();

	void setCursorVisability(bool is_visable);
	void setCursorPosition(int x, int y);
	
	void allowTexures2D(bool enabled);

	void enableDepthTest(bool enabled);

	void printSettings(void);

	void clearScreen();
	void swapBuffer();

	SDL_Window* _window;
	SDL_GLContext _opengl;

private:

	float m_width;
	float m_height;
	unsigned int m_flags;
	

	void createWindow(std::string name, GLuint x, GLuint y, GLuint w, GLuint h, GLuint flags);

};
#endif

