#include "TimeManager.h"

#include "TextRendererManager.h"

#include <iostream>

TimeManager::TimeManager()
{

}

void TimeManager::Tick()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	float FPS = (1 / deltaTime);
	TextRendererManager::GetInstance().RenderText(std::to_string(static_cast<int>(FPS)) + " FPS", 1920.0f - 150, 1080.0f - 48, 0.75f, glm::vec3(1.0f, 0.0f, 0.0f));
}

const float TimeManager::GetTime() const
{
	return glfwGetTime();
}

const float TimeManager::GetDeltaTime() const
{
	return deltaTime;
}