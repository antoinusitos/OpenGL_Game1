#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Camera;
class Shader;
class Shape;

class Entity
{
public:
	Entity(glm::vec3 positionIn);

	Shape* shape = nullptr;

	Entity* child = nullptr;

	std::string entityName = "";

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);

	void Render(Shader* ourShader, Camera* camera);

	void Free();
};

