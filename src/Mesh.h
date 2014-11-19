#pragma once
#ifndef MESH_H
#define MESH_H

#include "GameObject.h"

#include <glew.h>
#include <glm.hpp>
#include <vector>
#include "Vertex.h"

class Mesh : public GameObject
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(); // add default mesh - TODO
	~Mesh();	

	// getters
	unsigned int* getVAO_Id(void)							 { return &vao;							}
	unsigned int  getIndicesBufferId(void) const			 { return indices_buffer;				}
	bool          hasTexture(void)							 { return hasTextures;					}

	void render(unsigned int program_id);

	// game object overloaded functions
	void update(void);
	void render(void);
	

private:

	GLuint vao;
	GLuint vertices_buffer;
	GLuint indices_buffer;

	bool hasTextures;

};
#endif

