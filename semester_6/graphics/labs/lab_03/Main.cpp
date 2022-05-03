
#include "Components/Components.hpp"

#include "Systems/RenderSystem.hpp"
#include "WindowManager.hpp"
#include <chrono>
#include <random>
#include "Graphics/Mesh.h"
#include "Core/flecs.h"
#include "Systems/Systems.hpp"

static bool quit = false;

void QuitHandler(Event& event)
{
    quit = true;
}

int main()
{
    //gWorld->Init();

    //WindowManager windowManager;
    //windowManager.Init("Test", 1920, 1080, 0, 0);

    //gWorld->AddEventListener(FUNCTION_LISTENER(Events::Window::QUIT, QuitHandler));

    //gWorld->RegisterComponent<Camera>();
    //gWorld->RegisterComponent<Gravity>();
    //gWorld->RegisterComponent<Player>();
    //gWorld->RegisterComponent<Renderable>();
    //gWorld->RegisterComponent<RigidBody>();
    //gWorld->RegisterComponent<Thrust>();
    //gWorld->RegisterComponent<Transform>();
    //gWorld->RegisterComponent<MeshRenderer>();
    //gWorld->RegisterComponent<Material>();

    //auto cameraControlSystem = gWorld->RegisterSystem<CameraControlSystem>();
    //{
    //    Signature signature;
    //    signature.set(gWorld->GetComponentType<Camera>());
    //    signature.set(gWorld->GetComponentType<Transform>());
    //    gWorld->SetSystemSignature<CameraControlSystem>(signature);
    //}

    //cameraControlSystem->Init();


    //auto playerControlSystem = gWorld->RegisterSystem<PlayerControlSystem>();
    //{
    //    Signature signature;
    //    signature.set(gWorld->GetComponentType<Player>());
    //    signature.set(gWorld->GetComponentType<Transform>());
    //    gWorld->SetSystemSignature<PlayerControlSystem>(signature);
    //}

    //playerControlSystem->Init();


    //auto renderSystem = gWorld->RegisterSystem<RenderSystem>();
    //{
    //    Signature signature;
    //    signature.set(gWorld->GetComponentType<MeshRenderer>());
    //    signature.set(gWorld->GetComponentType<Transform>());
    //    gWorld->SetSystemSignature<RenderSystem>(signature);
    //}

    //renderSystem->Init();

    //std::vector<Entity> entities(MAX_ENTITIES - 1);

    //std::default_random_engine generator;
    //std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
    //std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    //std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
    //std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
    //std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

    //float scale = randScale(generator);
    //std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>(Mesh::sphere(1, 10, 10));

    //{
    //    auto entity = gWorld->CreateEntity();
    //    gWorld->AddComponent(
    //        entity,
    //        Transform{
    //            .position = glm::vec3(0),
    //            .rotation = glm::vec3(0),
    //            .scale = glm::vec3(1)
    //        });
    //    gWorld->AddComponent(
    //        entity,
    //        MeshRenderer{
    //            .mesh = sphereMesh
    //        });

    //}

    //float dt = 0.0f;

    //while (!quit)
    //{
    //    auto startTime = std::chrono::high_resolution_clock::now();

    //    windowManager.ProcessEvents();

    //    playerControlSystem->Update(dt);
    //    cameraControlSystem->Update(dt);
    //    renderSystem->Update(dt);

    //    windowManager.Update();

    //    auto stopTime = std::chrono::high_resolution_clock::now();

    //    dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    //}

    //windowManager.Shutdown();

    flecs::world world;

    renderSystem(world);

    auto e = world.entity();

    while (world.progress()) {}

    return 0;
}
