#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

class Plane : public Surface {
public:
	glm::vec3 plane_position;
	glm::vec3 plane_normal;
	float plane_distance;

	Plane(glm::vec3 plane_position, glm::vec3 plane_normal);

	float intersect(Ray ray, float t_min, float t_max); //returns -1 if there is no intersection.
	glm::vec3 get_normal(glm::vec3 point);
};

