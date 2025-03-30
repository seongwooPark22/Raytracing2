#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Ray.h"
#include "Material.h"

class Surface
{
public:
	Material material;

	Surface() {}
	virtual ~Surface() {}
	virtual float intersect(Ray ray, float t_min, float t_max) = 0;
	virtual glm::vec3 get_normal(glm::vec3 point) = 0;

	void set_material(Material material_info);
	glm::vec3 shade(Ray ray, glm::vec3 point, glm::vec3 surface_normal, const std::vector<Surface*>& objects, glm::vec3 light_position, float t_min, float t_max);
};

