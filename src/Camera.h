#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

#include <glm.hpp>

class WindowEngine;

class Camera : public GameObject
{
public:
	Camera(float aspect_ratio, float fov, float near_plane, float far_plane);
	~Camera();


	glm::mat4& getCombined();
	glm::mat4& getProjection();
	glm::mat4& getView();
	glm::mat4 getModelViewProjection(glm::mat4 model);

	//this will be used from a camera controller when more than one camera will be in the scene
	bool isActive();
	void setActive(bool a);

	void setMovementSpeed(float s);
	void setLookSpeed(float s);
	float getMovementSpeed();
	float getLookSpeed();

	// input is proccessed here - can be overriden to create a custom camera controller
	virtual void update(WindowEngine* window);

	void printViewMatrix();

private:
	float aspect_ratio;
	float fov;
	float near_plane;
	float far_plane;

	float movement_speed;
	float look_speed;
	float mouvementSpeed;

	bool m_active;

	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 m_combined;

	glm::vec3 m_target;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	glm::vec3 m_viewDirection;
};
#endif

