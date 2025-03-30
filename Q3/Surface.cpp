#include "Surface.h"

void Surface::set_material(Material material_info) {
	material = material_info;
}

glm::vec3 Surface::shade(Ray ray, glm::vec3 point, glm::vec3 surface_normal, const std::vector<Surface*>& objects, glm::vec3 light_position, float t_min, float t_max) {
	Ray shadow_ray = Ray(point, glm::normalize(light_position - point));

	glm::vec3 intensity = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 v = -glm::normalize(ray.dir);
	glm::vec3 l = glm::normalize(light_position - point);
	glm::vec3 h = glm::normalize(v + l);

	glm::vec3 L = material.ka * intensity; //ambient
	
	float min_tt = -1;
	for (int i = 0; i < objects.size(); i++) {
		min_tt = objects[i]->intersect(shadow_ray, t_min, t_max);
		if (min_tt != -1) {
			break;
		}
	}
	
	if (min_tt == -1) {
		L +=
			material.kd * intensity * glm::max(0.0f, glm::dot(surface_normal, l)) + //diffuse
			material.ks * intensity * glm::pow(glm::max(0.0f, glm::dot(surface_normal, h)), material.specular_power); //specular
	}
	return L;
}
