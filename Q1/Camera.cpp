#include "Camera.h"

Camera::Camera(int view_plane_width, int view_plane_height)
	: view_plane_width(view_plane_width), view_plane_height(view_plane_height) {}

Ray Camera::get_ray(int x, int y) {
	glm::vec3 pixel_pos = glm::vec3(
		l + (x + 0.5f)/view_plane_width * (r - l),
		b + (y + 0.5f)/view_plane_height * (t - b),
		eye_point.z - w.z * focal_length
	);

	return Ray(eye_point, glm::normalize(pixel_pos - eye_point));
}

