#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <gtx\transform.hpp>
#include <glm.hpp>

class Transform
{
public:
	Transform(const glm::vec3& translation = glm::vec3(0,0,0), const glm::vec3& rotation = glm::vec3(0,0,0), const glm::vec3& scale = glm::vec3(1,1,1))
		: position(translation),
		  rotation(rotation),
		  scale(scale)
	{

	}

	glm::mat4 getModelMatrix()
	{
		glm::mat4 Mtranslation = glm::translate(position);
		glm::mat4 Mscale       = glm::scale(scale);

		glm::mat4 MrotationX = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 MrotationY = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 MrotationZ = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

		glm::mat4 Mrotation = MrotationZ * MrotationY * MrotationX;

		return Mtranslation * Mrotation * Mscale;
	}

	glm::vec3& getPosition() { return position; }
	glm::vec3& getRotation() { return rotation; }
	glm::vec3& getScale()	 { return scale;    };


	void setPosition(glm::vec3 position) { this->position = position; }
	void setPosition(float x, float y, float z) { this->position.x = x; this->position.y = y; this->position.z = z; }
	void setPosX(float x) { this->position.x = x; }
	void setPosY(float y) { this->position.y = y; }
	void setPosZ(float z) { this->position.z = z; }

	void setRotation(glm::vec3 rotation) { this->rotation = rotation; }
	void setRotation(float x, float y, float z) { this->rotation.x = x; this->rotation.y = y; this->rotation.z = z; }
	void setRotX(float x) { this->rotation.x = x; }
	void setRotY(float y) { this->rotation.y = y; }
	void setRotZ(float z) { this->rotation.z = z; }

	void setScale(float scale) { this->scale = glm::vec3(scale, scale, scale); }
	void setScale(glm::vec3 scale) { this->scale = scale; }
	void setScale(float x, float y, float z) { this->scale.x = x; this->scale.y = y; this->scale.z = z; }	
	void setScaleX(float x) { this->scale.x = x; }	
	void setScaleY(float y) { this->scale.y = y; }	
	void setScaleZ(float z) { this->scale.z = z; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
#endif

