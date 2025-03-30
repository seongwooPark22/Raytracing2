#include "Scene.h"

Scene::Scene(glm::vec3 light_position) 
	: light_position(light_position) {}

Surface* Scene::add_object(Surface* object) {
	objects.push_back(object);
	return object;
}

glm::vec3 Scene::trace(Ray ray, float t_min, float t_max) {
	Surface* intersect_object = nullptr;
	float min_t = -1;

	//find the closest intersection's t.
	for (int i = 0; i < objects.size(); i++) { 
		float temp_t = objects[i]->intersect(ray, t_min, t_max);
		if ( temp_t != -1 && (min_t == -1 || temp_t < min_t)) {
			intersect_object = objects[i];
			min_t = temp_t;
		}
	}

	if ( min_t != -1 && intersect_object != nullptr ) {
		glm::vec3 intersection_point = ray.origin + ray.dir * (min_t); //the closest intersection point.
		glm::vec3 col = intersect_object->shade(
			ray, intersection_point,
			intersect_object->get_normal(intersection_point),
			objects,
			light_position,
			t_min, t_max
		);
		return col;
	}
	return glm::vec3(0.0f, 0.0f, 0.0f); //BLACK
}

Scene::~Scene() {
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}