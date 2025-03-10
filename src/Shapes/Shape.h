#pragma once

#include <glad/glad.h>;
#include <glm/glm.hpp>;

class Camera;
class Shader;

class Shape
{
public:
	virtual void Render(Shader* ourShader, Camera* camera, glm::vec3 positionIn, glm::vec3 rotationIn)
	{

	}
	virtual void Free()
	{

	}
};