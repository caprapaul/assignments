#pragma once

#include "../Core/System.hpp"

class Event;


class CameraControlSystem : public System
{
public:
	void Init() override;

	void Update(float dt) override;

private:
	std::bitset<8> mButtons;

	void InputListener(Event& event);
};
