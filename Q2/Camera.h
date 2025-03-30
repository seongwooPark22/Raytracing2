#pragma once

#include<glm/glm.hpp>
#include"Ray.h"

class Camera {
private:
	int view_plane_width; //resolution width
	int view_plane_height; //resolution height
	
	float l = -0.1f;
	float r = 0.1f;
	float b = -0.1f;
	float t = 0.1f;
	float focal_length = 0.1f;

	glm::vec3 eye_point = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 u = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 v = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 w = glm::vec3(0.0f, 0.0f, 1.0f);

public:
	Camera(int view_plane_width, int view_plane_height);
	Ray get_ray(int x, int y);
};
