#pragma once
#include "../Core/flecs.h"
#include "../Components/Components.hpp"

void renderSystem(const flecs::world& world) {
    auto cameraEntity = world.entity()
        .set<Transform>({ {0, 0, 500}, {0, 0, 0}, {1, 1, 1} })
        .set<Camera>({ Camera::makeProjectionTransform(45.0f, 0.1f, 1000.0f, 1920, 1080) });

    world.system()
        .kind(flecs::PreUpdate)
        .each([]() {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        });

    world.trigger<MeshRenderer>()
        .event(flecs::OnAdd)
        .each([](MeshRenderer& renderer) {
            unsigned int vao;
            unsigned int ebo;
            unsigned int vboVertices;

            auto vertices = renderer.mesh->vertices;
            auto indices = renderer.mesh->indices;

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            // Vertices
            glGenBuffers(1, &vboVertices);
            glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

            // Indices
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec3) * indices.size(), indices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);

            glBindVertexArray(0);

            renderer.vao = vao;
            renderer.vboVertices = vboVertices;
        });

    world.system<const Transform, MeshRenderer>()
        .kind(flecs::OnUpdate)
        .each([cameraEntity](const Transform& transform, MeshRenderer& renderer) {
            auto cameraTransform = cameraEntity.get<Transform>();
            auto camera = cameraEntity.get<Camera>();

            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            view = glm::translate(view, -cameraTransform->position);

            model = glm::translate(model, transform.position);
            model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

            projection = camera->projectionTransform;

            renderer.shader->use();
            renderer.shader->setMat4("model", model);
            renderer.shader->setMat4("view", view);
            renderer.shader->setMat4("projection", projection);

            glBindVertexArray(renderer.vao);
            glDrawElements(GL_TRIANGLES, renderer.mesh->indices.size(), GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);
        });
}

void windowSystem(const flecs::world& world) {
    world.trigger<Window>()
        .event(flecs::OnAdd)
        .each([](Window& window) {
            glfwInit();

            window.glfwWindow = glfwCreateWindow(window.width, window.height, window.title.c_str(), NULL, NULL);

            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
            glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // Create OpenGL Context
            glfwMakeContextCurrent(window.glfwWindow);
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            glfwSwapInterval(2);

            // Configure OpenGL
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glEnable(GL_DEPTH_TEST);
        });
}
