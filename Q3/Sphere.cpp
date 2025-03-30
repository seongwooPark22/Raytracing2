#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius) : position(position), radius(radius) {}

glm::vec3 Sphere::get_normal(glm::vec3 point) {
	return glm::normalize(point - position);
}

float Sphere::intersect(Ray ray, float t_min, float t_max) {  //returns -1 if there is no intersection.
	glm::vec3 np = ray.origin - position;

	float discriminant = glm::dot(ray.dir, np);
	discriminant *= discriminant;
	discriminant -= glm::dot(ray.dir, ray.dir) * (glm::dot(np, np) - radius*radius);

	if (discriminant < 0.0f) { //since it's discriminant, D < 0 -> no real root. -> no intersection!
		return -1; 
	}

	float t = -glm::dot(ray.dir, np);
	t = glm::min(t + glm::sqrt(discriminant), t - glm::sqrt(discriminant)) / glm::dot(ray.dir, ray.dir);

	if (t >= t_min and t <= t_max) {
		return t;
	}
	else {
		return -1;
	}
}

