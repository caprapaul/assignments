#pragma once

#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Graphics/Texture.hpp"
#include "../Graphics/Mesh.h"

struct Camera
{
	glm::mat4 projectionTransform;

	static glm::mat4 makeProjectionTransform(float fov, float nearClip, float farClip, unsigned int viewWidth, unsigned int viewHeight)
	{
		glm::mat4 projection = glm::perspective(fov, (float)viewWidth / (float)viewHeight, nearClip, farClip);

		return projection;
	}
};

struct Window {
	int width;
	int height;
	std::string title;

	GLFWwindow* glfwWindow;
};

struct MeshRenderer {
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Shader> shader;

	GLuint vao;
	GLuint ebo;
	GLuint vboVertices;
	GLuint vboNormals;
}; 

struct Material {
	Texture texture;
};

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
