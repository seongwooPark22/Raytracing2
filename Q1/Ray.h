#pragma once

#include<glm/glm.hpp>

class Ray
{
public:
	glm::vec3 origin;
	glm::vec3 dir;

	Ray(glm::vec3 origin, glm::vec3 dir) : origin(origin), dir(dir) {}
};

