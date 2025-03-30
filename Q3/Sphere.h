#pragma once

#include <glm/glm.hpp>

#include "Ray.h"
#include "Surface.h"

class Sphere : public Surface
{
public:
	glm::vec3 position;
	float radius;

	Sphere(glm::vec3 position, float radius);
	
	float intersect(Ray ray, float t_min, float t_max); //returns -1 if there is no intersection.
	glm::vec3 get_normal(glm::vec3 point);
};

