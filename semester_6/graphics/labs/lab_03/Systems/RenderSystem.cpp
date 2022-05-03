#include "RenderSystem.hpp"

#include "../Components/Camera.hpp"
#include "../Components/Renderable.hpp"
#include "../Components/Transform.hpp"
#include "../Core/World.hpp"
#include "../Graphics/Shader.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Components/MeshRenderer.hpp"

extern std::shared_ptr<World> gWorld;

void RenderSystem::Init()
{
	gWorld->AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));

	shader = std::make_unique<Shader>("./Shaders/vertex.glsl", "./Shaders/fragment.glsl");

	mCamera = gWorld->CreateEntity();

	gWorld->AddComponent(
		mCamera,
		Transform{
			.position = glm::vec3(0.0f, 0.0f, 500.0f)
		});

	gWorld->AddComponent(
		mCamera,
		Camera{
			.projectionTransform = Camera::MakeProjectionTransform(45.0f, 0.1f, 1000.0f, 1920, 1080)
		});

	for (auto const& entity : mEntities)
	{
		auto const& meshRenderer = gWorld->GetComponent<MeshRenderer>(entity);

		unsigned int vao;
		unsigned int vboVertices;

		std::vector<glm::vec3> vertices = meshRenderer.mesh->vertices;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Vertices
		glGenBuffers(1, &vboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);

		glBindVertexArray(0);
	}


}


void RenderSystem::Update(float dt)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT (hicpp-signed-bitwise)

	shader->use();
	glBindVertexArray(mVao);


	auto& cameraTransform = gWorld->GetComponent<Transform>(mCamera);
	auto& camera = gWorld->GetComponent<Camera>(mCamera);

	for (auto const& entity : mEntities)
	{
		auto const& transform = gWorld->GetComponent<Transform>(entity);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::translate(view, -cameraTransform.position);

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		projection = camera.projectionTransform;

		shader->setMat4("model", model);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);
}

void RenderSystem::WindowSizeListener(Event& event)
{
	auto windowWidth = event.GetParam<unsigned int>(Events::Window::Resized::WIDTH);
	auto windowHeight = event.GetParam<unsigned int>(Events::Window::Resized::HEIGHT);

	auto& camera = gWorld->GetComponent<Camera>(mCamera);
	camera.projectionTransform = Camera::MakeProjectionTransform(45.0f, 0.1f, 1000.0f, windowWidth, windowHeight);
}

