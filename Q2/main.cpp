#include <Windows.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <vector>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "Surface.h"
#include "Sphere.h"
#include "Plane.h"

///NEED TO BE ERASED BEFORE SUBMIT///
#include <random>
/////////////////////////////////////

// -------------------------------------------------
// Global Variables
// -------------------------------------------------
int Width = 512;
int Height = 512;
std::vector<float> OutputImage;
// -------------------------------------------------

glm::vec3 gamma_correction(glm::vec3 col, float gamma) {
	col.x = glm::pow(col.x, 1.0f/gamma);
	col.y = glm::pow(col.y, 1.0f/gamma);
	col.z = glm::pow(col.z, 1.0f/gamma);

	return col;
}

void set_pixel(std::vector<float>& image, const glm::vec3& color) {
	image.push_back(color.x); // R
	image.push_back(color.y); // G
	image.push_back(color.z); // B
}

void render(Camera& camera, Scene& scene)
{
	OutputImage.clear();

	for (int j = 0; j < Height; j++) {
		for (int i = 0; i < Width; i++) {
			Ray ray = camera.get_ray(i, j);
			glm::vec3 col = scene.trace(ray, 0.01f, 99999.0f);
			col = gamma_correction(col, 2.2f);
			set_pixel(OutputImage, col);
		}
	}
}

void resize_callback(GLFWwindow*, int nw, int nh)
{
	//This is called in response to the window resizing.
	//The new width and height are passed in so we make 
	//any necessary changes:
	Width = nw;
	Height = nh;
	//Tell the viewport to use all of our screen estate
	glViewport(0, 0, nw, nh);

	//This is not necessary, we're just working in 2d so
	//why not let our spaces reflect it?
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, static_cast<double>(Width)
		, 0.0, static_cast<double>(Height)
		, 1.0, -1.0);

	//Reserve memory for our render so that we don't do 
	//excessive allocations and render the image
	OutputImage.reserve(Width * Height * 3);

	glm::vec3 light_position = glm::vec3(-4.0f, 4.0f, -3.0f);

	Camera camera = Camera(Width, Height);
	Scene scene = Scene(light_position);

	scene.add_object(new Plane(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)))
		->set_material(
			Material(
				glm::vec3(0.2f, 0.2f, 0.2f), 
				glm::vec3(1.0f, 1.0f, 1.0f), 
				glm::vec3(0.0f, 0.0f, 0.0f), 0.0f
			)
		);

	scene.add_object(new Sphere(glm::vec3(-4.0f, 0.0f, -7.0f), 1.0f))
		->set_material(
			Material(
				glm::vec3(0.2f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f), 0.0f
			)
		);

	scene.add_object(new Sphere(glm::vec3(0.0f, 0.0f, -7.0f), 2.0f))
	->set_material(
		Material(
			glm::vec3(0.0f, 0.2f, 0.0f),
			glm::vec3(0.0f, 0.5f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.5f), 32.0f
		)
	);

	scene.add_object(new Sphere(glm::vec3(4.0f, 0.0f, -7.0f), 1.0f))
	->set_material(
		Material(
			glm::vec3(0.0f, 0.0f, 0.2f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f), 0.0f
		)
	);

	render(camera, scene);
}


int main(int argc, char* argv[])
{
	// -------------------------------------------------
	// Initialize Window
	// -------------------------------------------------

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Width, Height, "Q2", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//We have an opengl context now. Everything from here on out 
	//is just managing our window or opengl directly.

	//Tell the opengl state machine we don't want it to make 
	//any assumptions about how pixels are aligned in memory 
	//during transfers between host and device (like glDrawPixels(...) )
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	//We call our resize function once to set everything up initially
	//after registering it as a callback with glfw
	glfwSetFramebufferSizeCallback(window, resize_callback);
	resize_callback(NULL, Width, Height);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// -------------------------------------------------------------
		//Rendering begins!
		glDrawPixels(Width, Height, GL_RGB, GL_FLOAT, &OutputImage[0]);
		//and ends.
		// -------------------------------------------------------------

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//Close when the user hits 'q' or escape
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}