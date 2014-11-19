#include "Mesh.h"
#include "Logger.h"
#include "RenderingEngine.h"
#include "Shader.h"
#include "cout.h"

#include <scene.h>
#include <postprocess.h>
#include <Importer.hpp>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	this->setName("mesh");
	this->getVerticesCount() = vertices.size();
	this->getIndicesCount() = indices.size(); 
	this->getFacesCount() = indices.size() / 3;
	

	// generate all the buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vertices_buffer);
	glGenBuffers(1, &indices_buffer);

	//used to eliminate clutter - instead of calling renderer->getBoundProgram()->hasAttributePosition()
	ShaderProgram* program = ShaderProgramCache::getProgram("default shader");

	//add the data to the indices buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//add the data to vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	// tell opengl how the vertices buffer is layed out
	{
		// Positions
		if (program->getAttributeLocation("position") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("position"));
			glVertexAttribPointer(program->getAttributeLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		}
		
		// Texture Coordinates
		if (program->getAttributeLocation("uv") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("uv"));
			glVertexAttribPointer(program->getAttributeLocation("uv"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		}

		if (program->getAttributeLocation("normal") != -1)
		{
			// Normals
			glEnableVertexAttribArray(program->getAttributeLocation("normal"));
			glVertexAttribPointer(program->getAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		}

		// Tangents
		if (program->getAttributeLocation("tangent") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("tangent"));
			glVertexAttribPointer(program->getAttributeLocation("tangent"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		}

		if (program->getAttributeLocation("colour") != -1)
		{
			// Colours
			glEnableVertexAttribArray(program->getAttributeLocation("colour"));
			glVertexAttribPointer(program->getAttributeLocation("colour"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		}
	}

	// unbind the bound arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);

	glDeleteBuffers(1, &vertices_buffer);
	glDeleteBuffers(1, &indices_buffer);
}

void Mesh::update()
{
	
}



void Mesh::render()
{
	renderer->render(this);
}

void Mesh::render(unsigned int program_id)
{
	glUseProgram(program_id);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	glBindVertexArray(0);
	glUseProgram(0);
}
