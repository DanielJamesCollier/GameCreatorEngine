#include "WindowEngine.h"
#include "Logger.h"

#include <iostream>
#include <sstream>

WindowEngine::WindowEngine()
{
	createWindow("default window", 100, 100, 100, 100, 1);
}

WindowEngine::WindowEngine(std::string title, GLuint x, GLuint y, GLuint w, GLuint h, GLuint flags)
{
	this->m_width = w;
	this->m_height = h;
	createWindow(title, x, y, w, h, flags);

	Logger::infoBlock("Window Created", "Title: " + title + "\nx pos: " + std::to_string(x) + "\ny pos: " + std::to_string(y) + "\nwidth: " +  std::to_string(w) + "\nheight: " + std::to_string(h), true);
}

WindowEngine::~WindowEngine()
{
	SDL_GL_DeleteContext(_opengl);
	SDL_DestroyWindow(_window);
}

void WindowEngine::createWindow(std::string name, GLuint x, GLuint y, GLuint w, GLuint h, GLuint flags)
{

	SDL_Init(SDL_INIT_VIDEO);

	// set the opengl context version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	// turn on double buffering set the depth buffer to 24 bits
	// you may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

	_window = SDL_CreateWindow(name.c_str(), x, y, w, h, flags);
	_opengl = SDL_GL_CreateContext(_window);

	glewExperimental = GL_TRUE;

	glViewport(0, 0, w, h);

	//SDL_GL_SetAttribute(SDL_GL_STEREO, 1);

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(status) << "\n";
	
	}

	// sync buffer swap with monitor's vertical refresh rate
	SDL_GL_SetSwapInterval(1);

	// set background color
	glClearColor(0.0f, 0.2f, 0.4f, 1.0f);

	//printSettings();

	// flips the backbuffer to avoid screen flicker in engine initialisation
	this->clearScreen();
	this->swapBuffer();

}

void WindowEngine::setCursorVisability(bool is_visable)
{
	if (is_visable) SDL_ShowCursor(SDL_ENABLE);
	else SDL_ShowCursor(SDL_DISABLE);
}

void WindowEngine::setCursorPosition(int x, int y)
{
	SDL_WarpMouseInWindow(_window, x, y);
}

void WindowEngine::allowTexures2D(bool enabled)
{
	if (enabled) glEnable(GL_TEXTURE_2D);
	else	     glDisable(GL_TEXTURE_2D);
	
}

float& WindowEngine::getWidth()
{
	return m_width;
}

float& WindowEngine::getHeight()
{
	return m_height;
}

float d = SDL_GetTicks();

void WindowEngine::clearScreen()
{
	d += 0.005;

	const float clearcolour[] = {
		
		sin(d), 
		cos(d), 
		0, 
		1.0f 
	
	};

	const float black[] = {

		1,1,1,1

	};

	const float white[] = {

		0,0,0,0

	};



	glClearBufferfv(GL_COLOR, 0, white);

	glClear(GL_DEPTH_BUFFER_BIT);
}

void WindowEngine::swapBuffer()
{
	SDL_GL_SwapWindow(_window);
}

void WindowEngine::printSettings()
{
	int opengl_major, opengl_minor; 
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &opengl_major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &opengl_minor);

	int red_size, green_size, blue_size, alpha_size, buffer_size;
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red_size);
	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &green_size);
	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &blue_size);
	SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &alpha_size);
	SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &buffer_size);

	int double_buffered, depth_size;
	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &double_buffered);
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depth_size);

	int multisample_buffers, multisamples;
	SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &multisample_buffers);
	SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &multisamples);

	std::stringstream settings;

	settings << "Opengl Major: " << opengl_major << "\n";
	settings << "Opengl Minor: " << opengl_minor << "\n";

	settings << "Red Size: " << red_size << "\n";
	settings << "Green Size: " << green_size << "\n";
	settings << "Blue Size: " << blue_size << "\n";
	settings << "Alpha Size: " << alpha_size << "\n";
	settings << "Buffer Size: " << buffer_size << "\n";

	settings << "Double Buffered: " << double_buffered << "\n";
	settings << "Depth Buffer Size: " << depth_size << "\n";

	settings << "Multisample Buffers: " << multisample_buffers << "\n";
	settings << "Multisamles: " << multisamples << "\n";

	Logger::infoBlock("Window Engine Settings", settings.str(), true);


}