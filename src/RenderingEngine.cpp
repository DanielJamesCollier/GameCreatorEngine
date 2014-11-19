#include "RenderingEngine.h"
#include "WindowEngine.h"
#include "TextureCache.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Sprite.h"
#include "cout.h"

RenderingEngine::RenderingEngine(WindowEngine* window)
{
	this->window = window;
	window->setCursorVisability(false);

	main_camera = new Camera(window->getWidth() / window->getHeight(), 70.0f, 0.1f, 10000.0f);
	textures	= new TextureCache();

	program_cache = new ShaderProgramCache();

	bound_program = ShaderProgramCache::getProgram("default shader");

	/* RENDER SETTINGS */
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_CLAMP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


RenderingEngine::~RenderingEngine()
{
	delete main_camera;
	delete shaders;
	delete window;
	delete program_cache;
}

void RenderingEngine::setCamera(Camera* camera)
{
	this->main_camera = camera;
}

ShaderProgram* RenderingEngine::getBoundProgram()
{
	return bound_program;
}

GLuint RenderingEngine::getBoundProgramId()
{
	return bound_program->getID();
}

void RenderingEngine::updateCamera()
{
	main_camera->update(window);
}

float timex = 0;

void RenderingEngine::render(Sprite* sprite)
{
	// check if the bound program is the one that needs to be used
	if (bound_program->getID() == ShaderProgramCache::getProgram("sprite shader")->getID())
	{
		glUseProgram(bound_program->getID());
	}

	glBindVertexArray(*sprite->getVAO_Id());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->getIndicesBufferId());
	{
		bound_program->setUniform4m("mvp", main_camera->getModelViewProjection(sprite->getModelMatrix()));
		glDrawElements(GL_TRIANGLES, sprite->getIndicesCount(), GL_UNSIGNED_INT, 0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void RenderingEngine::render(Sprite* sprite, ShaderProgram* program)
{
	
	glUseProgram(program->getID());
	

	glBindVertexArray(*sprite->getVAO_Id());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->getIndicesBufferId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->texture_id);
	glUniform1i(program->getUniformLocation("texture0"), 0);

	timex += 0.00001;
	program->setUniform1f("timex", timex);

	program->setUniform4m("mvp", main_camera->getModelViewProjection(sprite->getModelMatrix()));
	glDrawElements(GL_TRIANGLES, sprite->getIndicesCount(), GL_UNSIGNED_INT, 0);

	glBindTexture(sprite->getTexture()->texture_type, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

float time = 0;

void RenderingEngine::render(Mesh* mesh)
{
	if (bound_program->getID() == ShaderProgramCache::getProgram("default shader")->getID())
	{
		glUseProgram(bound_program->getID());
	}
	
	glBindVertexArray(*mesh->getVAO_Id());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndicesBufferId());

	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureCache::getTexture("Textures/dave.png")->texture_id);
	glUniform1i(bound_program->UNIFORM_TEXTURE0, 0);*/

	time += 0.00001;

	bound_program->setUniform1f("time", time);

	bound_program->setUniform4m("mvp", main_camera->getModelViewProjection(mesh->getModelMatrix()));
	glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);

		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void RenderingEngine::render(Mesh* mesh, ShaderProgram* program)
{
	glUseProgram(program->getID());
	glBindVertexArray(*mesh->getVAO_Id());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndicesBufferId());


	program->setUniform4m("mvp", main_camera->getModelViewProjection(mesh->getModelMatrix()));
	glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	

}

void RenderingEngine::clearScreen()
{
	window->clearScreen();
}

void RenderingEngine::swapBackBuffer()
{
	window->swapBuffer();
}


