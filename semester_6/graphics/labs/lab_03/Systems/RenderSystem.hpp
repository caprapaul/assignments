#pragma once

#include "../Core/System.hpp"
#include "../Graphics/Shader.hpp"
#include <memory>

class Event;

class RenderSystem : public System
{
public:
	void Init() override;

	void Update(float dt) override;

private:
	void WindowSizeListener(Event& event);

	std::unique_ptr<Shader> shader;

	Entity mCamera;
};
