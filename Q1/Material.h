#pragma once
#include<glm/glm.hpp>

class Material
{
public:
	glm::vec3 ka = glm::vec3(0.0f, 0.0f, 0.0f); //ambient 
	glm::vec3 kd = glm::vec3(0.0f, 0.0f, 0.0f); //diffuse
	glm::vec3 ks = glm::vec3(0.0f, 0.0f, 0.0f); //specular
	float specular_power = 0.0f;

	Material() {}
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specular_power)
		: ka(ambient), kd(diffuse), ks(specular), specular_power(specular_power) {}
};

