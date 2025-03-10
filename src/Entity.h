#pragma once

#include <glad/glad.h>;
#include <glm/glm.hpp>;

class Camera;
class Shader;
class Shape;

class Entity
{
public:
	Entity(glm::vec3 positionIn);

	Shape* shape = nullptr;

	glm::vec3 position;

	void Render(Shader* ourShader, Camera* camera);

	void Free();
};

