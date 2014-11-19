#include "Camera.h"
#include "Logger.h"
#include "Input.h"
#include "WindowEngine.h"
#include <gtx\transform.hpp>
#include <gtc\type_ptr.hpp>
#include <string>
#include <sstream>

Camera::Camera(float aspect_ratio, float fov, float near_plane, float far_plane)
	: GameObject("Camera")
{
	m_forward = glm::vec3(0, 0, -1);
	m_up = glm::vec3(0, 1, 0);
	setMovementSpeed(0.2f);
	setLookSpeed(0.2);
	mouvementSpeed = 3;
	//app->setCursorPosition(app->getWidth() / 2, app->getHeight() / 2);

	this->m_projection = glm::perspective(fov, aspect_ratio, near_plane, far_plane);
	this->m_view = glm::lookAt(getPosition(), getPosition() + m_viewDirection, m_up);
	this->m_viewDirection = glm::vec3(0, 0, -1);
}

Camera::~Camera()
{

}

glm::mat4& Camera::getCombined()
{
	m_combined = m_projection * m_view;
	return m_combined;
}

glm::mat4& Camera::getProjection()
{
	return m_projection;
}

glm::mat4& Camera::getView()
{
	return m_view;
}

glm::mat4 Camera::getModelViewProjection(glm::mat4 model)
{
	return getCombined() * model;
}

bool Camera::isActive()
{
	return m_active;
}

void Camera::setActive(bool a)
{
	m_active = a;
}

void Camera::setMovementSpeed(float s)
{
	movement_speed = s;
}

void Camera::setLookSpeed(float s)
{
	look_speed = s;
}

float Camera::getMovementSpeed()
{
	return movement_speed;
}

float Camera::getLookSpeed()
{
	return look_speed;
}

void Camera::printViewMatrix()
{
	double dArray[16] = { 0.0 };

	const float *pSource = (const float*)glm::value_ptr(m_view);
	for (int i = 0; i < 16; ++i)
		dArray[i] = pSource[i];

	std::stringstream stream;

	for (int i = 0; i < 16; ++i)
	{
		if (i == 4 || i == 8 || i == 12) stream << "\n";

		if (dArray[i] < 0)
		{
			stream << dArray[i];
		} 
		
		if (dArray[i] >= 0)
		{
			stream << " " << dArray[i];
		}

		stream << " ";
	}

	Logger::infoBlock("camera view matrix", stream.str(), true);
}

bool mouse_in = true;

glm::vec2 mouseDelta;


// TODO needs optimizing
void Camera::update(WindowEngine* window)
{
	if (Input::isKeyPressed(SDL_SCANCODE_ESCAPE) && mouse_in)
	{
		mouse_in = false;
		window->setCursorVisability(true);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_F) && !mouse_in)
	{
		mouse_in = true;
		window->setCursorVisability(false);
	}

	if (mouse_in)
	{
		glm::vec3 cam_position = getPosition();
		if (Input::isKeyPressed(SDL_SCANCODE_W)) setPosition(cam_position + m_viewDirection * movement_speed);
		if (Input::isKeyPressed(SDL_SCANCODE_S)) setPosition(cam_position - m_viewDirection * movement_speed);

		// the right vector for the camera
		glm::vec3 right = glm::cross(m_up, m_viewDirection);

		if (Input::isKeyPressed(SDL_SCANCODE_A)) setPosition(cam_position + right * movement_speed);
		if (Input::isKeyPressed(SDL_SCANCODE_D)) setPosition(cam_position - right * movement_speed);
		
		// calculates the delta x and y for the mouse position
		const int midX = window->getWidth() / 2;
		const int midY = window->getHeight() / 2;

		int mouseX = Input::getX();
		int mouseY = Input::getY();
		{
			mouseDelta.x = (float)(midX - mouseX);
			mouseDelta.y = (float)(midY - mouseY);
		}
		if (mouse_in)window->setCursorPosition(midX, midY);

		//rotate around x and y
		m_viewDirection = glm::mat3(glm::rotate(mouseDelta.x * look_speed, m_up)) * m_viewDirection;
		m_viewDirection = glm::mat3(glm::rotate(-mouseDelta.y * look_speed, right)) * m_viewDirection;

		// update the view matrix
		m_target = getPosition() + m_viewDirection;
		m_view = glm::lookAt(getPosition(), m_target, m_up);
	}
}
