#ifndef LIGHTS_H
#define LIGHTS_H
#pragma once

#include <glm.hpp>

struct DirectionalLight
{
	glm::vec3 colour;
	float ambientIntensity;
};

#endif